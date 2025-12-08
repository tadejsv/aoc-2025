#include <cstddef>
#include <print>
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

void
track_beam(
    const Point& start,
    const std::unordered_map<size_t, std::vector<size_t>>& reflectors,
    std::unordered_set<size_t>& splits
) {
    if (!reflectors.contains(start.second) || splits.contains(hash_point(start))) {
        return;
    }
    for (auto y_ind : reflectors.at(start.second)) {
        if (y_ind < start.first) {
            continue;
        }
        if (splits.contains((hash_point({ y_ind, start.second })))) {
            break;
        }

        splits.insert(hash_point({ y_ind, start.second }));
        track_beam({ y_ind + 1, start.second - 1 }, reflectors, splits);
        track_beam({ y_ind + 1, start.second + 1 }, reflectors, splits);

        break;
    }
};

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day7.txt") };

    Point start{};
    std::unordered_map<size_t, std::vector<size_t>> reflectors{};

    for (size_t i{ 0 }; i < lines.size(); ++i) {
        for (size_t j{ 0 }; j < lines[0].size(); ++j) {
            switch (lines[i][j]) {
                case 'S':
                    start = { i, j };
                    break;
                case '^':
                    reflectors[j].push_back(i);
                    break;
            }
        }
    }

    std::unordered_set<size_t> splits{};
    track_beam(start, reflectors, splits);

    std::println("Splits: {}", splits.size());
}