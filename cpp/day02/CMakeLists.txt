# add_executable(Day2 main.cpp)
add_executable(Day2 main2.cpp)

target_link_libraries(Day2 PUBLIC compiler_flags utils)

configure_file(../../inputs/day2_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day2_test.txt COPYONLY)
configure_file(../../inputs/day2.txt ${CMAKE_CURRENT_BINARY_DIR}/day2.txt COPYONLY)
