cmake_minimum_required(VERSION 3.31)

project(AOC2024
    VERSION 1.0
    LANGUAGES CXX
)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_23)

add_subdirectory(utils)

add_subdirectory(day01)
add_subdirectory(day02)
add_subdirectory(day03)
add_subdirectory(day04)
