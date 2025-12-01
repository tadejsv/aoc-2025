# add_executable(Day1 main.cpp)
add_executable(Day1 main2.cpp)

target_link_libraries(Day1 PUBLIC compiler_flags utils)

configure_file(../../inputs/day1_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day1_test.txt COPYONLY)
configure_file(../../inputs/day1.txt ${CMAKE_CURRENT_BINARY_DIR}/day1.txt COPYONLY)
