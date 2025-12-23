#include <cmath>
#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <vector>

#include "utils/utils.h"

using Point = std::pair<int64_t, int64_t>;
using Edge = std::pair<Point, Point>;

auto
rect_area(const Point& point1, const Point& point2) -> int64_t {
    return (std::abs(point1.first - point2.first) + 1)
           * (std::abs(point1.second - point2.second) + 1);
}

auto
valid_rect(const Point& p1, const Point& p2, const std::vector<Edge>& shape) -> bool {
    const int64_t minX = std::min(p1.first, p2.first);
    const int64_t maxX = std::max(p1.first, p2.first);
    const int64_t minY = std::min(p1.second, p2.second);
    const int64_t maxY = std::max(p1.second, p2.second);

    for (const auto& e : shape) {
        const auto& a = e.first;
        const auto& b = e.second;

        const int64_t eMinX = std::min(a.first, b.first);
        const int64_t eMaxX = std::max(a.first, b.first);
        const int64_t eMinY = std::min(a.second, b.second);
        const int64_t eMaxY = std::max(a.second, b.second);

        // Same strict overlap test as in your Go code:
        // minX < eMaxX && maxX > eMinX && minY < eMaxY && maxY > eMinY
        const bool overlaps = (minX < eMaxX) && (maxX > eMinX) && (minY < eMaxY) && (maxY > eMinY);

        if (overlaps) {
            return false;
        }
    }

    return true;
}

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day9.txt") };
    std::vector<Point> points{};

    for (const auto& line : lines) {
        const auto parts{ utils::split_string(line, ",") };
        points.emplace_back(std::stoll(parts[0]), std::stoll(parts[1]));
    }

    std::vector<Edge> shape{};
    for (size_t i{ 0 }; i < points.size() - 1; ++i) {
        shape.emplace_back(points[i], points[i + 1]);
    }
    shape.emplace_back(points[points.size() - 1], points[0]);

    int64_t max_area{ 0 };
    for (size_t i{ 0 }; i < points.size(); ++i) {
        for (size_t j{ i + 1 }; j < points.size(); ++j) {
            const auto area = rect_area(points[i], points[j]);
            if (area > max_area) {
                if (valid_rect(points[i], points[j], shape)) {
                    max_area = area;
                }
            }
        }
    }

    std::println("{}", max_area);
}