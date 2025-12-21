# add_executable(Day10 main.cpp)
add_executable(Day10 main2.cpp)

target_link_libraries(Day10 PUBLIC compiler_flags utils Eigen3::Eigen)

configure_file(../../inputs/day10_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day10_test.txt COPYONLY)
configure_file(../../inputs/day10.txt ${CMAKE_CURRENT_BINARY_DIR}/day10.txt COPYONLY)
