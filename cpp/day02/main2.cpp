#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <unordered_set>

#include "utils/utils.h"

constexpr auto
pow10(size_t n) -> int64_t {
    int64_t result = 1;
    while (n-- > 0) {
        result *= 10;
    }
    return result;
}

auto
repeat_num(int64_t num, size_t times) -> int64_t {
    std::string num_str{ std::to_string(num) };
    std::string result{};
    while (times-- > 0) {
        result += num_str;
    }
    return std::stol(result);
}

void
get_repeating_nums(
    std::unordered_set<int64_t>& seen,
    const std::string& num,
    const int64_t n1,
    const int64_t n2,
    bool go_up
) {
    const int64_t incr = go_up ? 1 : -1;
    for (size_t i{ 1 }; i <= num.size() / 2; ++i) {
        if (num.size() % i != 0) {
            continue;
        }

        const size_t rep{ num.size() / i };
        const auto p1{ num.substr(0, i) };
        const int64_t ppow{ pow10(p1.size()) };
        for (int64_t num_part{ std::stoll(p1) }; num_part >= ppow / 10 && num_part < ppow;
             num_part += incr) {
            const auto new_num{ repeat_num(num_part, rep) };
            if (new_num > n2 || new_num < n1) {
                continue;
            }
            seen.insert(new_num);
        }
    }
};

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day2.txt") };
    const auto parts{ utils::split_string(lines[0], ",") };

    int64_t sum{ 0 };
    for (const auto& part : parts) {
        std::unordered_set<int64_t> seen{};
        const auto nums{ utils::split_string(part, "-") };
        const int64_t n1{ std::stol(nums[0]) };
        const int64_t n2{ std::stol(nums[1]) };

        get_repeating_nums(seen, nums[0], n1, n2, true);
        if (nums[1].size() > nums[0].size()) {
            get_repeating_nums(seen, nums[1], n1, n2, false);
        }
        for (const auto num : seen) {
            sum += num;
        }
    }

    std::println("Sum: {}", sum);
}