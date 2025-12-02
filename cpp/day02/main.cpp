#include <cstddef>
#include <cstdint>
#include <print>
#include <string>

#include "utils/utils.h"

constexpr auto
pow10(size_t n) -> int64_t {
    int64_t result = 1;
    while (n-- > 0) {
        result *= 10;
    }
    return result;
}

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day2.txt") };
    const auto parts{ utils::split_string(lines[0], ",") };

    int64_t sum{ 0 };
    for (const auto& part : parts) {
        const auto nums{ utils::split_string(part, "-") };
        const int64_t n1{ std::stol(nums[0]) };
        const int64_t n2{ std::stol(nums[1]) };

        if (nums[0].size() % 2 == 1 && nums[0].size() == nums[1].size()) {
            continue;
        }

        if (nums[0].size() % 2 == 0) {
            const auto h1{ nums[0].substr(0, nums[0].size() / 2) };
            const int64_t hpow{ pow10(h1.size()) };

            for (int64_t half{ std::stol(h1) }; half < hpow; ++half) {
                const auto new_num{ half * hpow + half };
                if (new_num > n2 || new_num < n1) {
                    continue;
                }
                sum += new_num;
            }
        } else if (nums[1].size() % 2 == 0) {
            const auto h1{ nums[1].substr(0, nums[1].size() / 2) };
            const int64_t hpow{ pow10(h1.size()) };

            for (int64_t half{ std::stol(h1) }; half >= hpow / 10; --half) {
                const auto new_num{ half * hpow + half };
                if (new_num > n2 || new_num < n1) {
                    continue;
                }
                sum += new_num;
            }
        }
    }

    std::println("Sum: {}", sum);
}