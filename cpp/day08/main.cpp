#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <print>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils/utils.h"

struct Dist {
    float dist{};
    size_t from{};
    size_t to{};
};

auto
find_root(const size_t node, std::unordered_map<size_t, size_t>& roots) -> size_t {
    size_t root{ node };
    while (true) {
        const auto new_root{ roots[root] };
        if (new_root == root) {
            break;
        }
        root = new_root;
    }
    return root;
};

void
join(
    const size_t i,
    const size_t j,
    std::unordered_map<size_t, size_t>& roots,
    std::unordered_map<size_t, int32_t>& sizes
) {
    auto ri{ find_root(i, roots) };
    auto rj{ find_root(j, roots) };

    if (ri == rj) {
        return;
    }

    roots[rj] = ri;
    sizes[ri] += sizes[rj];
}

int
main() {  // NOLINT

    const auto lines{ utils::read_lines_from_file("day8.txt") };
    std::vector<std::array<int64_t, 3>> points{};

    for (const auto& line : lines) {
        const auto parts{ utils::split_string(line, ",") };
        points.push_back({ std::stoll(parts[0]), std::stoll(parts[1]), std::stoll(parts[2]) });
    }

    std::vector<Dist> dists{};

    for (size_t i{ 0 }; i < points.size(); ++i) {
        for (size_t j{ i + 1 }; j < points.size(); ++j) {
            const std::array<int64_t, 3>& p1{ points[i] };
            const std::array<int64_t, 3>& p2{ points[j] };

            float dist = std::sqrt(
                static_cast<float>(
                    (p1.at(0) - p2.at(0)) * (p1.at(0) - p2.at(0))
                    + (p1.at(1) - p2.at(1)) * (p1.at(1) - p2.at(1))
                    + (p1.at(2) - p2.at(2)) * (p1.at(2) - p2.at(2))
                )
            );

            dists.emplace_back(dist, i, j);
        }
    }

    std::ranges::sort(dists, [](const Dist& a, const Dist& b) -> bool { return a.dist < b.dist; });

    std::unordered_map<size_t, size_t> roots{};
    std::unordered_map<size_t, int32_t> sizes{};
    for (size_t i{ 0 }; i < points.size(); ++i) {
        roots[i] = i;
        sizes[i] = 1;
    }


    std::span<Dist> top_dists(dists.data(), 1000);
    for (const auto& dist : top_dists) {
        join(dist.from, dist.to, roots, sizes);
    }

    std::unordered_set<size_t> seen{};
    std::vector<int32_t> final_sizes{};
    for (size_t i{ 0 }; i < points.size(); ++i) {
        const auto root{ find_root(i, roots) };
        if (!seen.contains(root)) {
            final_sizes.push_back(sizes[root]);
            seen.insert(root);
        }
    }

    std::ranges::sort(final_sizes, std::greater<int32_t>{});

    const auto result = final_sizes[0] * final_sizes[1] * final_sizes[2];
    std::println("{}", result);
}