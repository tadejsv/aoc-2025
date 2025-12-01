#include <cstddef>
#include <cstdint>
#include <print>
#include <string>

#include "utils/utils.h"

int
main() {  // NOLINT
    const auto& lines{ utils::read_lines_from_file("day1.txt") };

    int32_t position{ 50 };

    int32_t count{ 0 };
    for (const auto& line : lines) {
        const auto dir{ line[0] };
        const int32_t turn = std::stoi(line.substr(1, line.size()));

        if (dir == 'L') {
            position -= turn;
        } else {
            position += turn;
        }

        position %= 100;
        if (position < 0) {
            position += 100;
        }


        if (position == 0) {
            ++count;
        }
    }

    std::println("Total count: {}", count);
}