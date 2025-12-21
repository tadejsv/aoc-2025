# add_executable(Day8 main.cpp)
add_executable(Day8 main2.cpp)

target_link_libraries(Day8 PUBLIC compiler_flags utils)

configure_file(../../inputs/day8_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day8_test.txt COPYONLY)
configure_file(../../inputs/day8.txt ${CMAKE_CURRENT_BINARY_DIR}/day8.txt COPYONLY)
