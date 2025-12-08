# add_executable(Day7 main.cpp)
add_executable(Day7 main2.cpp)

target_link_libraries(Day7 PUBLIC compiler_flags utils)

configure_file(../../inputs/day7_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day7_test.txt COPYONLY)
configure_file(../../inputs/day7.txt ${CMAKE_CURRENT_BINARY_DIR}/day7.txt COPYONLY)
