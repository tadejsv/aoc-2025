#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <vector>

#include "utils/utils.h"

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day3.txt") };

    std::vector<std::vector<int32_t>> nums;
    for (const auto& line : lines) {
        std::vector<int32_t> line_nums{};
        for (const auto c : line) {
            line_nums.push_back(c - '0');
        }
        nums.push_back(line_nums);
    }

    int32_t sum{ 0 };
    for (const auto& line_nums : nums) {
        size_t max_ind{ 0 };
        int32_t max{ 0 };

        for (size_t i{ 0 }; i < line_nums.size() - 1; ++i) {
            if (line_nums[i] > max) {
                max = line_nums[i];
                max_ind = i;
            }
        }

        int32_t max2{ 0 };
        for (size_t i{ max_ind + 1 }; i < line_nums.size(); ++i) {
            max2 = std::max(line_nums[i], max2);
        }

        sum += max * 10 + max2;
    }

    std::println("{}", sum);
}