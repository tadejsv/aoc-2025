#include <cstddef>
#include <cstdint>
#include <print>
#include <string>

#include "utils/utils.h"

int
main() {  // NOLINT
    const auto& lines{ utils::read_lines_from_file("day1.txt") };

    int32_t position{ 50 };
    int32_t prev_pos{ 50 };

    int32_t count{ 0 };
    for (const auto& line : lines) {
        const auto dir{ line[0] };
        int32_t turn = std::stoi(line.substr(1));
        if (dir == 'L') {
            turn = -turn;
        }
        position += turn;

        if (turn > 0) {
            count += (position) / 100;
        } else {
            count += std::abs((position - 100) / 100);
            if (prev_pos == 0) {
                count = std::max(0, count - 1);
            }
        }

        position %= 100;
        position = (position + 100) % 100;

        prev_pos = position;
    }

    std::println("Total count: {}", count);
}