# add_executable(Day3 main.cpp)
add_executable(Day3 main2.cpp)

target_link_libraries(Day3 PUBLIC compiler_flags utils)

configure_file(../../inputs/day3_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day3_test.txt COPYONLY)
configure_file(../../inputs/day3.txt ${CMAKE_CURRENT_BINARY_DIR}/day3.txt COPYONLY)
