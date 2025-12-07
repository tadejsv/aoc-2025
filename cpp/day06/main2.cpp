#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <utility>
#include <vector>

#include "utils/utils.h"

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day6.txt") };

    std::vector<std::pair<char, size_t>> symbols{};
    const auto& last_line{ lines[lines.size() - 1] };
    for (size_t i{ 0 }; i < last_line.size(); ++i) {
        if (last_line[i] != ' ') {
            symbols.emplace_back(last_line[i], i);
        }
    }

    std::vector<std::vector<int32_t>> equation_nums(symbols.size());
    for (size_t si{ 0 }; si < symbols.size(); ++si) {
        size_t end{};
        if (si == symbols.size() - 1) {
            end = last_line.size();
        } else {
            end = symbols[si + 1].second - 1;
        }

        for (size_t ci{ symbols[si].second }; ci < end; ++ci) {
            int32_t num{ 0 };
            for (size_t i{ 0 }; i < lines.size() - 1; ++i) {
                if (lines[i][ci] == ' ') {
                    continue;
                }
                int32_t current{ lines[i][ci] - '0' };
                num = 10 * num + current;
            }
            equation_nums[si].push_back(num);
        }
    }

    int64_t total_sum{ 0 };
    for (size_t si{ 0 }; si < symbols.size(); ++si) {
        int64_t result{ symbols[si].first == '+' ? 0 : 1 };
        for (const auto num : equation_nums[si]) {
            if (symbols[si].first == '+') {
                result += num;
            } else {
                result *= num;
            }
        }
        total_sum += result;
    }
    std::println("{}", total_sum);
}