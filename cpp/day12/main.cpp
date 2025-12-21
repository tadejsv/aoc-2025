#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <vector>

#include "utils/utils.h"

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day12.txt") };

    int32_t result{};
    for (const auto& line : lines) {
        if (!line.contains('x')) {
            continue;
        }

        const auto parts{ utils::split_string(line, ": ") };
        const auto area_parts{ utils::split_string(parts[0], "x") };
        int32_t area{ std::stoi(area_parts[0]) * std::stoi(area_parts[1]) };

        const auto num_parts{ utils::split_string(parts[1], " ") };
        std::vector<int32_t> nums{};
        nums.reserve(num_parts.size());
        for (const auto& num_part : num_parts) {
            nums.push_back(std::stoi(num_part));
        }

        int32_t nums_sum{ 0 };
        for (auto num : nums) {
            nums_sum += num;
        }

        if (nums_sum * 8 < area) {
            ++result;
        }
    }

    std::println("{}", result);
}