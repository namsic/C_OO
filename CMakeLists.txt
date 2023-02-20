cmake_minimum_required(VERSION 3.25)

project(NamsiClang)

include_directories(include)
add_compile_options(-Werror)

enable_testing()

add_subdirectory(lib)
add_subdirectory(test)