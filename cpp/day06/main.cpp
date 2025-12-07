#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <vector>

#include "utils/utils.h"

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day6.txt") };

    std::vector<std::vector<int32_t>> line_nums{};
    for (const auto& line : lines) {
        if (line == lines[lines.size() - 1]) {
            break;
        }
        std::vector<int32_t> nums_line{};
        const auto parts{ utils::split_string(line, " ") };
        for (const auto& part : parts) {
            if (part.size() != 0) {
                nums_line.push_back(std::stoi(part));
            }
        }
        line_nums.push_back(nums_line);
    }

    // Get symbols
    std::vector<std::string> symbols{};
    for (const auto& part : utils::split_string(lines[lines.size() - 1], " ")) {
        if (part.size() != 0) {
            symbols.push_back(part);
        }
    }

    int64_t total_sum{ 0 };
    for (size_t i{ 0 }; i < symbols.size(); ++i) {
        int64_t result{ symbols[i] == "+" ? 0 : 1 };
        for (size_t j{ 0 }; j < line_nums.size(); ++j) {
            if (symbols[i] == "+") {
                result += line_nums[j][i];
            } else {
                result *= line_nums[j][i];
            }
        }
        total_sum += result;
    }

    std::println("{}", total_sum);
}