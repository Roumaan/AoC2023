cmake_minimum_required(VERSION 3.26)
cmake_policy(SET CMP0005 NEW)
project(AoC2023_solutions)

set(CMAKE_CXX_STANDARD 14)

set(Days 01 02 03)

foreach (day ${Days})
    add_executable(${day}a src/${day}/main.cc)
    set(FILE_PATH "${CMAKE_SOURCE_DIR}/input/${day}/a.txt")
    file(TO_CMAKE_PATH "${FILE_PATH}" FILE_PATH_NORMALIZED)
    target_compile_definitions(${day}a PRIVATE AOC_INPUT_FILE="${FILE_PATH_NORMALIZED}")

    add_executable(${day}a_t src/${day}/main.cc)
    set(FILE_PATH "${CMAKE_SOURCE_DIR}/input/${day}/a_test.txt")
    file(TO_CMAKE_PATH "${FILE_PATH}" FILE_PATH_NORMALIZED)
    target_compile_definitions(${day}a_t PRIVATE AOC_INPUT_FILE="${FILE_PATH_NORMALIZED}")

    add_executable(${day}b src/${day}/main.cc)
    set(FILE_PATH "${CMAKE_SOURCE_DIR}/input/${day}/b.txt")
    file(TO_CMAKE_PATH "${FILE_PATH}" FILE_PATH_NORMALIZED)
    target_compile_definitions(${day}b PRIVATE AOC_PART_2 AOC_INPUT_FILE="${FILE_PATH_NORMALIZED}")

    add_executable(${day}b_t src/${day}/main.cc)
    set(FILE_PATH "${CMAKE_SOURCE_DIR}/input/${day}/b_test.txt")
    file(TO_CMAKE_PATH "${FILE_PATH}" FILE_PATH_NORMALIZED)
    target_compile_definitions(${day}b_t PRIVATE AOC_PART_2 AOC_INPUT_FILE="${FILE_PATH_NORMALIZED}")
endforeach ()