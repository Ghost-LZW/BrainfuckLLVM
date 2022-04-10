cmake_minimum_required(VERSION 3.10)

project(Brainfuck VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(BrainfuckIncludePath ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BrainfuckLibraryPath ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BrainfuckToolsPath ${CMAKE_CURRENT_SOURCE_DIR}/tools)

set(CMAKE_CXX_FLAGS "-g -Wall -Werror")

configure_file(${BrainfuckIncludePath}/BrainfuckConfig.h.in ${BrainfuckIncludePath}/BrainfuckConfig.h)

include_directories(${BrainfuckIncludePath})

add_subdirectory(${BrainfuckLibraryPath})
add_subdirectory(${BrainfuckToolsPath})
