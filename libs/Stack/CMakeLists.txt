cmake_minimum_required(VERSION 3.15)

set(STACK_SRC_DIR "src")
set(STACK_INCLUDE_DIR "include")

add_library(Stack STATIC "${STACK_SRC_DIR}/Stack.cpp")

target_include_directories(Stack PUBLIC
                            "${CMAKE_CURRENT_SOURCE_DIR}/include")