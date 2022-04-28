cmake_minimum_required(VERSION 3.14)

project(Brainfuck VERSION 0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

# don't work like expect
# llvm_map_components_to_libnames(llvm_libs support core irreader x86codegen x86asmparser asmparser asmprinter)

set(llvm_libs "LLVM-13")

message(STATUS "llvm " ${llvm_libs})

set(BrainfuckIncludePath ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(BrainfuckLibraryPath ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BrainfuckToolsPath ${CMAKE_CURRENT_SOURCE_DIR}/tools)

set(CMAKE_CXX_FLAGS "-g -Wall -Werror")

configure_file(${BrainfuckIncludePath}/BrainfuckConfig.h.in ${BrainfuckIncludePath}/BrainfuckConfig.h)

include_directories(${BrainfuckIncludePath})

add_subdirectory(${BrainfuckLibraryPath})
add_subdirectory(${BrainfuckToolsPath})
