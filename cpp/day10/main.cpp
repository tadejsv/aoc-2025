#include <bit>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <print>
#include <string>
#include <vector>

#include "utils/utils.h"

struct QueueItem {
    uint32_t state;
    uint32_t pressed;
    size_t from;
};

int
main() {  // NOLINT

    const auto lines{ utils::read_lines_from_file("day10.txt") };

    int32_t result{ 0 };
    for (const auto& line : lines) {
        const auto parts{ utils::split_string(line, " ") };

        uint32_t goal{ 0 };
        size_t goal_size{ parts[0].size() - 2 };
        for (size_t i{ 0 }; i < goal_size; ++i) {
            if (parts[0][goal_size + 1 - (i + 1)] == '#') {
                goal |= 1 << i;
            }
        }

        std::vector<uint32_t> buttons{};
        for (size_t i{ 1 }; i < parts.size() - 1; ++i) {
            const auto button_parts{
                utils::split_string(parts[i].substr(1, parts[i].size() - 2), ",")
            };
            uint32_t button{};
            for (const auto& button_part : button_parts) {
                button |= 1 << (goal_size - 1 - std::stoul(button_part));
            }
            buttons.push_back(button);
        }

        std::deque<QueueItem> queue{ { 0, 0, 0 } };

        int32_t min_steps{ 0 };
        while (!queue.empty()) {
            const auto item = queue.front();
            queue.pop_front();
            if (item.state == goal) {
                min_steps = std::popcount(item.pressed);
                break;
            }

            if (std::popcount(item.pressed) + 1 > buttons.size()) {
                break;
            }
            for (size_t i{ item.from }; i < buttons.size(); ++i) {
                if (((1 << i) & item.pressed) == 0) {
                    queue.emplace_back(item.state ^ buttons[i], item.pressed | (1 << i), i);
                }
            }
        }
        result += min_steps;
    }

    std::println("{}", result);
}