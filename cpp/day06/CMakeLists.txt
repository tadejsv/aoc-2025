# add_executable(Day6 main.cpp)
add_executable(Day6 main2.cpp)

target_link_libraries(Day6 PUBLIC compiler_flags utils)

configure_file(../../inputs/day6_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day6_test.txt COPYONLY)
configure_file(../../inputs/day6.txt ${CMAKE_CURRENT_BINARY_DIR}/day6.txt COPYONLY)
