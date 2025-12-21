# add_executable(Day11 main.cpp)
add_executable(Day11 main2.cpp)

target_link_libraries(Day11 PUBLIC compiler_flags utils)

configure_file(../../inputs/day11_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day11_test.txt COPYONLY)
configure_file(../../inputs/day11.txt ${CMAKE_CURRENT_BINARY_DIR}/day11.txt COPYONLY)
