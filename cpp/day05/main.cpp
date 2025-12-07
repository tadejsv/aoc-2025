#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <utility>
#include <vector>

#include "utils/utils.h"

using Interval = std::pair<int64_t, int64_t>;

auto
check_in_intervals(int64_t num, const std::vector<Interval>& intervals) -> bool {
    for (const auto& interval : intervals) {
        if (num < interval.first) {
            return false;
        }
        if (num > interval.second) {
            continue;
        }
        return true;
    }
    return false;
};

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day5.txt") };

    std::vector<int64_t> nums{};
    std::vector<Interval> initial_intervals{};
    bool individual{ false };
    for (const auto& line : lines) {
        if (line.size() == 0) {
            individual = true;
            continue;
        }

        if (individual) {
            nums.push_back(std::stoll(line));
        } else {
            const auto parts{ utils::split_string(line, "-") };
            initial_intervals.emplace_back(std::stoll(parts[0]), std::stoll(parts[1]));
        }
    }

    std::vector<Interval> intervals{};
    std::ranges::sort(initial_intervals, [](Interval a, Interval b) -> bool {
        return (a.first == b.first) ? a.second < b.second : a.first < b.first;
    });

    int64_t curr_start{ initial_intervals[0].first };
    int64_t curr_end{ initial_intervals[0].second };

    for (const auto& interval : initial_intervals) {
        if (interval.first > curr_end) {
            intervals.emplace_back(curr_start, curr_end);
            curr_start = interval.first;
            curr_end = interval.second;
        } else {
            curr_end = std::max(curr_end, interval.second);
        }
    }
    intervals.emplace_back(curr_start, curr_end);

    int64_t count{ 0 };
    for (const auto num : nums) {
        if (check_in_intervals(num, intervals)) {
            ++count;
        }
    }
    std::println("{}", count);
}