#include <algorithm>
#include <chrono>
#include <fstream>  // IWYU pragma: keep
#include <iostream>
#include <ranges>
#include <string_view>
#include <vector>

#include "utils/utils.h"

namespace utils {

    auto trim(const std::string& str) -> std::string {
        // Find the first non-whitespace character from the beginning
        auto start = std::ranges::find_if_not(str, [](unsigned char chr) {
            return std::isspace(chr);
        });

        // Find the first non-whitespace character from the end
        auto end = std::ranges::find_if_not(std::ranges::reverse_view(str), [](unsigned char chr) {
            return std::isspace(chr);
        });

        // Return the trimmed string
        return (start < end.base() ? std::string(start, end.base()) : std::string());
    }

    auto split_string(std::string_view str, std::string_view split_by) -> std::vector<std::string> {
        std::vector<std::string> parts;

        auto parts_view = std::views::split(str, split_by);

        // Convert each subrange into a std::string
        for (auto&& subrange : parts_view) {
            parts.emplace_back(subrange.begin(), subrange.end());
        }

        return parts;
    }

    auto read_lines_from_file(const std::string& fname) -> std::vector<std::string> {
        std::ifstream file{ fname };
        std::vector<std::string> lines;

        // Leaving this like this until I learn about C++ exception/error handling :)))
        if (!file.is_open()) {
            std::cerr << "Can't read the file :("
                      << "\n";
            return lines;
        }

        std::string line;
        while (getline(file, line)) {
            lines.push_back(line);
        }

        return lines;
    }

    auto Timer::reset() -> void {
        m_beg = Clock::now();
    };

    auto Timer::elapsed() const -> double {
        return std::chrono::duration_cast<Second>(Clock::now() - m_beg).count();
    };
}  // namespace utils
