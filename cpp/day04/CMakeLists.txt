# add_executable(Day4 main.cpp)
add_executable(Day4 main2.cpp)

target_link_libraries(Day4 PUBLIC compiler_flags utils)

configure_file(../../inputs/day4_test.txt ${CMAKE_CURRENT_BINARY_DIR}/day4_test.txt COPYONLY)
configure_file(../../inputs/day4.txt ${CMAKE_CURRENT_BINARY_DIR}/day4.txt COPYONLY)
