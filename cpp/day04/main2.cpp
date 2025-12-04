#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <mdspan>
#include <print>
#include <string>
#include <vector>

#include "utils/utils.h"

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day4.txt") };

    std::vector<uint8_t> flat_grid(lines[0].size() * lines.size());
    auto grid = std::mdspan(flat_grid.data(), lines.size(), lines[0].size());

    for (size_t i{ 0 }; i < lines.size(); ++i) {
        for (size_t j{ 0 }; j < lines[i].size(); ++j) {
            if (lines[i][j] == '@') {
                grid[i, j] = 1;
            }
        }
    }

    int32_t prev_premoved{ -1 };
    int32_t removed{ 0 };
    while (removed > prev_premoved) {
        prev_premoved = removed;
        for (size_t i{ 0 }; i < grid.extent(0); ++i) {
            for (size_t j{ 0 }; j < grid.extent(1); ++j) {
                if (grid[i, j] == 0) {
                    continue;
                }
                int32_t count_neighbors{ 0 };
                for (size_t ii = (i > 0) ? i - 1 : 0; ii < std::min(i + 2, grid.extent(0)); ++ii) {
                    for (size_t jj = (j > 0) ? j - 1 : 0; jj < std::min(j + 2, grid.extent(1)); ++jj) {
                        if (i == ii && j == jj) {
                            continue;
                        }
                        count_neighbors += grid[ii, jj];
                    }
                }

                if (count_neighbors < 4) {
                    ++removed;
                    grid[i, j] = 0;
                }
            }
        }
    }

    std::println("{}", removed);
}