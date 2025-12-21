#include <cstddef>
#include <cstdint>
#include <deque>
#include <print>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.h"

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day11.txt") };

    Graph graph{};
    for (const auto& line : lines) {
        const auto parts{ utils::split_string(line, " ") };

        std::string from = parts[0].substr(0, 3);
        graph[from] = std::vector<std::string>(parts.begin() + 1, parts.end());
    }


    std::deque<std::string> queue{ "you" };

    int32_t paths{ 0 };
    while (!queue.empty()) {
        const std::string node = queue.front();
        queue.pop_front();

        if (node == "out") {
            ++paths;
            continue;
        }

        if (graph.contains(node)) {
            for (const auto& neighbor : graph[node]) {
                queue.push_back(neighbor);
            }
        }
    }

    std::println("{}", paths);
}