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

    const size_t NUM_DIGITS{ 12 };
    int64_t sum{ 0 };
    for (const auto& line_nums : nums) {
        size_t start_ind{ 0 };
        int64_t line_sum{ 0 };
        for (size_t i{ 1 }; i <= NUM_DIGITS; ++i) {
            int32_t max_digit{ -1 };
            size_t max_ind{ 0 };
            for (size_t j{ start_ind }; j < line_nums.size() - (NUM_DIGITS - i); ++j) {
                if (line_nums[j] > max_digit) {
                    max_digit = line_nums[j];
                    max_ind = j;
                }
            }
            start_ind = max_ind + 1;
            line_sum = line_sum * 10 + max_digit;
        }

        sum += line_sum;
    }

    std::println("{}", sum);
}