# add_executable(Day5 main.cpp)
add_executable(Day5 main2.cpp)

target_link_libraries(Day5 PUBLIC compiler_flags utils)

configure_file(../../inputs/day5_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day5_test.txt COPYONLY)
configure_file(../../inputs/day5.txt ${CMAKE_CURRENT_BINARY_DIR}/day5.txt COPYONLY)
