#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <iostream>
#include <print>
#include <string>
#include <tuple>
#include <vector>

#include "utils/utils.h"

using MatrixI = Eigen::Matrix<int32_t, Eigen::Dynamic, Eigen::Dynamic>;

static auto
igcd(int64_t a, int64_t b) -> int64_t {
    a = std::abs(a);
    b = std::abs(b);
    return std::gcd(a, b);
}

static auto
row_gcd(const MatrixI::RowXpr& r) -> int64_t {
    int64_t g = 0;
    for (Eigen::Index j = 0; j < r.cols(); ++j) {
        int64_t v = r(j);
        if (v != 0) {
            g = (g == 0) ? std::abs(v) : igcd(g, v);
        }
    }
    return g;
}

static void
normalize_row(MatrixI::RowXpr r) {
    int64_t g = row_gcd(r);
    if (g > 1) {
        r /= g;
    }

    // Optional: make first non-zero entry positive (keeps a more canonical form)
    for (Eigen::Index j = 0; j < r.cols(); ++j) {
        if (r(j) != 0) {
            if (r(j) < 0) {
                r *= -1;
            }
            break;
        }
    }
}

void
reduce_matrix(MatrixI& m) {
    int64_t pivot_row = 0;
    int64_t pivot_col = 0;

    while (pivot_col < (m.cols() - 1) && pivot_row < m.rows()) {
        // Find a row with non-zero pivot in this column
        int64_t sel = -1;
        for (int64_t i = pivot_row; i < m.rows(); ++i) {
            if (m(i, pivot_col) != 0) {
                sel = i;
                break;
            }
        }
        if (sel == -1) {
            ++pivot_col;
            continue;
        }

        if (sel != pivot_row) {
            m.row(sel).swap(m.row(pivot_row));
        }

        const int64_t p = m(pivot_row, pivot_col);

        // Zero out the pivot column in other rows using fraction-free elimination
        for (int64_t i = 0; i < m.rows(); ++i) {
            if (i == pivot_row) {
                continue;
            }

            const int64_t a = m(i, pivot_col);
            if (a == 0) {
                continue;
            }

            const int64_t g = igcd(p, a);
            const int64_t mul_i = p / g;  // scale target row
            const int64_t mul_p = a / g;  // scale pivot row

            // row_i = row_i * mul_i - row_pivot * mul_p
            m.row(i) = (m.row(i) * mul_i - m.row(pivot_row) * mul_p).eval();

            normalize_row(m.row(i));
        }

        ++pivot_col;
        ++pivot_row;
    }

    // Final pass: divide each row by gcd of its non-zero entries
    for (int64_t r = 0; r < m.rows(); ++r) {
        normalize_row(m.row(r));
    }
}

inline auto
complement_indices(Eigen::Index n, std::vector<int> excl) -> Eigen::VectorXi {
    std::ranges::sort(excl);
    Eigen::VectorXi keep(n - (int) excl.size());
    int k = 0;
    int e = 0;
    for (int i = 0; i < n; ++i) {
        if (e < (int) excl.size() && excl[e] == i) {
            ++e;
            continue;
        }
        keep[k++] = i;
    }
    return keep;
}

auto
simplify_problem(const MatrixI& m) -> std::tuple<MatrixI, int32_t, int32_t> {
    std::vector<int32_t> solved_cols{};
    std::vector<int32_t> solved_rows{};
    int32_t partial_result{ 0 };

    for (int32_t i{ 0 }; i < m.rows(); ++i) {
        int32_t non_zeros{ 0 };
        int32_t non_zero_ind{ 0 };
        for (int32_t j{ 0 }; j < m.cols() - 1; ++j) {
            if (m(i, j) != 0) {
                ++non_zeros;
                non_zero_ind = j;
            }
        }
        if (non_zeros == 1) {
            solved_cols.push_back(non_zero_ind);
            solved_rows.push_back(i);
            partial_result += m(i, m.cols() - 1);
        } else if (non_zeros == 0) {
            solved_rows.push_back(i);
        }
    }

    if (solved_cols.size() == m.cols() - 1) {
        return { {}, partial_result, 0 };
    }

    auto keep_rows = complement_indices(m.rows(), solved_rows);
    auto keep_cols = complement_indices(m.cols(), solved_cols);

    const auto rhs_col = static_cast<int32_t>(m.cols() - 1);

    std::vector<int32_t> fixed_cols;  // <= 1 non-zero
    std::vector<int32_t> free_cols;   // > 1 non-zero
    fixed_cols.reserve(keep_cols.size());
    free_cols.reserve(keep_cols.size());

    for (int col : keep_cols) {
        if (col == rhs_col) {
            continue;  // RHS handled at the end
        }

        int32_t cnt = 0;
        for (int keep_row : keep_rows) {
            if (m(keep_row, col) != 0) {
                ++cnt;
                if (cnt > 1) {
                    break;
                }
            }
        }

        (cnt > 1 ? free_cols : fixed_cols).push_back(col);
    }

    // ordered: fixed first, then free, then RHS last
    Eigen::VectorXi ordered_cols(keep_cols.size());
    int32_t out = 0;
    for (int32_t c : fixed_cols) {
        ordered_cols[out++] = c;
    }
    for (int32_t c : free_cols) {
        ordered_cols[out++] = c;
    }
    ordered_cols[out++] = rhs_col;

    MatrixI sub = m(keep_rows, Eigen::placeholders::all)(Eigen::placeholders::all, ordered_cols);
    return { sub, partial_result, free_cols.size() };
}

constexpr int32_t MAX_VAL{ 266 };

auto
check_solution(
    const MatrixI& coeffs,
    Eigen::VectorXi sums,
    const int32_t free_vars,
    const Eigen::VectorXi& vals
) -> int32_t {
    const int64_t cols{ coeffs.cols() };
    for (int64_t i{ 0 }; i < free_vars; ++i) {
        sums -= vals[i] * coeffs.col(cols - free_vars + i);
    }

    Eigen::VectorXi vals_not_free = Eigen::VectorXi::Zero(cols - free_vars);
    for (int32_t i{ 0 }; i < cols - free_vars; ++i) {
        const auto coeff = coeffs(i, i);
        const auto val = sums(i);
        if (coeff <= 0 || (val % coeff != 0 && val > 0) || val < 0) {
            return -1;
        }
        vals_not_free(i) = val / coeff;
    }

    return vals_not_free.sum() + vals.sum();
};

inline static auto
check_solution_fast(
    const MatrixI& coeffs,     // (rows x cols_no_rhs)
    const Eigen::VectorXi& b,  // (rows)
    int32_t free_vars,
    const Eigen::VectorXi& free_vals  // pointer to f[0..free_vars-1]
) -> int32_t {
    const auto cols = static_cast<int32_t>(coeffs.cols());
    const int32_t nfix = cols - free_vars;  // number of non-free vars
    const int32_t free0 = nfix;             // first free col index

    int32_t total = free_vals.sum();

    // For each fixed row i, compute residual r = b_i - sum_j a_ij * f_j
    for (int i = 0; i < nfix; ++i) {
        int32_t r = b(i);
        const auto row = coeffs.row(i);

        // subtract contributions of free variables
        for (int j = 0; j < free_vars; ++j) {
            r -= row(free0 + j) * free_vals[j];
        }

        const int32_t d = row(i);  // diagonal coefficient
        if (d <= 0 || r < 0 || (r % d != 0)) {
            return -1;
        }

        total += r / d;
    }
    // std::println("{} {}", total, free_vals);

    return total;
}

inline static auto
initial_upper_bounds_for_free(
    const MatrixI& coeffs,     // m.leftCols(m.cols()-1)
    const Eigen::VectorXi& b,  // m.col(m.cols()-1)
    int32_t free_vars,
    int32_t hard_cap  // e.g. MAX_VAL
) -> std::vector<int32_t> {
    const int32_t cols = (int32_t) coeffs.cols();
    const int32_t nfix = cols - free_vars;
    const int32_t free0 = nfix;

    std::vector<int32_t> ub(free_vars, hard_cap);

    for (int j = 0; j < free_vars; ++j) {
        int32_t best = hard_cap;

        for (int i = 0; i < nfix; ++i) {
            bool mixed = false;
            for (int k = 0; k < free_vars; ++k) {
                if (k != j && coeffs(i, free0 + k) < 0) {
                    mixed = true;
                    break;
                }
            }
            if (mixed) {
                continue;
            }
            const int64_t di = coeffs(i, i);
            if (di <= 0) {
                continue;  // only gives "sum a f <= b" when di > 0
            }

            const int64_t a = coeffs(i, free0 + j);
            const int64_t bi = b(i);

            if (bi <= 0 || a <= 0) {
                continue;
            }

            best = std::min<int32_t>(best, (int32_t) (bi / a));
        }

        ub[j] = best;
    }

    return ub;
}

auto
solve_problem(const MatrixI& m, int32_t free_vars) -> int32_t {
    if (m.rows() == 0) {
        return 0;
    }

    // loop over all possible permutations
    Eigen::VectorXi vals = Eigen::VectorXi::Zero(free_vars);

    int32_t min_val{ std::numeric_limits<int32_t>::max() };

    const MatrixI coeffs = m.leftCols(m.cols() - 1);
    const MatrixI sums = m.col(m.cols() - 1);

    auto ub = initial_upper_bounds_for_free(coeffs, sums, free_vars, MAX_VAL);
    while (true) {
        // auto solution = check_solution(coeffs, sums, free_vars, vals);
        auto solution = check_solution_fast(coeffs, sums, free_vars, vals);

        if (solution > -1) {
            min_val = std::min(solution, min_val);
        }

        int32_t i = 0;
        for (; i < vals.size(); ++i) {
            if (vals[i] < ub[i] + 10) {
                ++vals[i];
                break;
            }
            vals[i] = 0;
        }
        if (i == vals.size()) {
            break;
        }
    }

    return min_val;
}

int
main() {  // NOLINT

    const auto lines{ utils::read_lines_from_file("day10.txt") };

    int64_t result{ 0 };
    for (const auto& line : lines) {
        const auto parts{ utils::split_string(line, " ") };

        // Read in joltages
        std::vector<int32_t> joltages{};
        const auto& last{ parts[parts.size() - 1] };
        const auto joltages_strs{ utils::split_string(last.substr(1, last.size() - 2), ",") };
        joltages.reserve(joltages_strs.size());
        for (const auto& part : joltages_strs) {
            joltages.push_back(std::stoi(part));
        }

        // Read in buttons
        std::vector<std::vector<int32_t>> buttons{};
        for (size_t i{ 1 }; i < parts.size() - 1; ++i) {
            std::vector<int32_t> button{};
            const auto& button_str{ parts[i] };
            const auto button_parts{
                utils::split_string(button_str.substr(1, button_str.size() - 2), ",")
            };
            button.reserve(button_parts.size());
            for (const auto& bp : button_parts) {
                button.push_back(std::stoi(bp));
            }
            buttons.push_back(button);
        }

        // Convert everything to a matrix
        MatrixI m = MatrixI::Zero(joltages.size(), buttons.size() + 1);

        for (size_t i{ 0 }; i < joltages.size(); ++i) {
            m(i, buttons.size()) = joltages[i];
        }
        for (size_t i{ 0 }; i < buttons.size(); ++i) {
            for (const auto j : buttons[i]) {
                m(j, i) = 1;
            }
        }

        reduce_matrix(m);
        const auto [sub_m, pr, free_vars] = simplify_problem(m);
        // std::cout << m << "\n\n" << sub_m << "\n\n";
        auto solution = solve_problem(sub_m, free_vars);
        std::println("{} {} {}", pr, solution, sub_m.cols());

        if (solution > 10000) {
            std::println("{}", line);
        }
        result += pr + solution;
    }

    std::println("{}", result);
}