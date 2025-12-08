#include <cstddef>
#include <cstdint>
#include <iterator>
#include <optional>
#include <print>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include "utils/utils.h"

constexpr const size_t HASH_CONST{ 1000 };

using Point = std::pair<size_t, size_t>;

auto
hash_point(const Point& p) -> size_t {
    return p.first * HASH_CONST + p.second;
}

auto
find_reflector(const Point& start, const std::unordered_map<size_t, std::vector<size_t>>& reflectors)
    -> std::optional<Point> {
    if (!reflectors.contains(start.second)) {
        return {};
    }
    for (auto y_ind : reflectors.at(start.second)) {
        if (y_ind < start.first) {
            continue;
        }

        return Point{ y_ind, start.second };
    }
    return {};
};

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day7.txt") };

    Point start{};
    std::vector<Point> all_reflectors{};
    std::unordered_map<size_t, std::vector<size_t>> reflectors{};

    for (size_t i{ 0 }; i < lines.size(); ++i) {
        for (size_t j{ 0 }; j < lines[0].size(); ++j) {
            switch (lines[i][j]) {
                case 'S':
                    start = { i, j };
                    break;
                case '^':
                    all_reflectors.emplace_back(i, j);
                    reflectors[j].push_back(i);
                    break;
            }
        }
    }

    std::unordered_map<size_t, int64_t> paths{};
    auto start_ref{ find_reflector(start, reflectors) };
    paths[hash_point(start_ref.value())] = 1;

    int64_t total{ 0 };
    for (const auto& reflector : all_reflectors) {
        int64_t ref_paths{ paths[hash_point(reflector)] };
        if (ref_paths == 0) {
            continue;
        }

        const auto ref1{ find_reflector({ reflector.first, reflector.second - 1 }, reflectors) };
        const auto ref2{ find_reflector({ reflector.first, reflector.second + 1 }, reflectors) };

        if (ref1) {
            paths[hash_point(ref1.value())] += ref_paths;
        } else {
            total += ref_paths;
        }
        if (ref2) {
            paths[hash_point(ref2.value())] += ref_paths;
        } else {
            total += ref_paths;
        }
    }

    std::println("Paths: {}", total);
}
