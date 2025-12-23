# add_executable(Day9 main.cpp)
add_executable(Day9 main2.cpp)

target_link_libraries(Day9 PUBLIC compiler_flags utils)

configure_file(../../inputs/day9_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day9_test.txt COPYONLY)
configure_file(../../inputs/day9.txt ${CMAKE_CURRENT_BINARY_DIR}/day9.txt COPYONLY)
