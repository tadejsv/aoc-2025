#include <cstddef>
#include <cstdint>
#include <print>
#include <string>
#include <unordered_map>
#include <vector>

#include "utils/utils.h"

using Graph = std::unordered_map<std::string, std::vector<std::string>>;

struct Path {
    std::string current;
    bool visited_dac;
    bool visited_fft;
};

auto
make_key(const Path& p) -> std::string {
    return p.current + (p.visited_dac ? "1" : "0") + (p.visited_fft ? "1" : "0");
}

auto
search_paths(const Path& path, Graph& graph, std::unordered_map<std::string, int64_t>& memo)
    -> int64_t {
    if (path.current == "out") {
        return (path.visited_dac && path.visited_fft) ? 1 : 0;
    }

    const auto path_key = make_key(path);
    if (memo.contains(path_key)) {
        return memo[path_key];
    }

    int64_t total{ 0 };
    for (const auto& neighbor : graph[path.current]) {
        total += search_paths(
            {
                .current = neighbor,
                .visited_dac = path.visited_dac || (path.current == "dac"),
                .visited_fft = path.visited_fft || (path.current == "fft"),
            },
            graph,
            memo
        );
    }

    memo[path_key] = total;

    return total;
};

int
main() {  // NOLINT
    const auto lines{ utils::read_lines_from_file("day11.txt") };

    Graph graph{};
    for (const auto& line : lines) {
        const auto parts{ utils::split_string(line, " ") };

        std::string from = parts[0].substr(0, 3);
        graph[from] = std::vector<std::string>(parts.begin() + 1, parts.end());
    }

    std::unordered_map<std::string, int64_t> memo{};
    int64_t result{
        search_paths({ .current = "svr", .visited_dac = false, .visited_fft = false }, graph, memo)
    };

    std::println("{}", result);
}
