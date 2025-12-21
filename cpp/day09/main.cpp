#include <algorithm>
#include <array>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <print>
#include <span>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "utils/utils.h"

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day9.txt") };
    std::vector<std::pair<int64_t, int64_t>> points{};

    for (const auto& line : lines) {
        const auto parts{ utils::split_string(line, ",") };
        points.emplace_back(std::stoll(parts[0]), std::stoll(parts[1]));
    }

    int64_t max_area{ 0 };
    for (size_t i{ 0 }; i < points.size(); ++i) {
        for (size_t j{ i + 1 }; j < points.size(); ++j) {
            const auto area = (std::abs(points[i].first - points[j].first) + 1)
                              * (std::abs(points[i].second - points[j].second) + 1);
            max_area = std::max(area, max_area);
        }
    }

    std::println("{}", max_area);
}