cmake_minimum_required(VERSION 3.15)

set(STACK_SRC_DIR "src")
set(STACK_INCLUDE_DIR "include")
set(STACK_TEST_DIR "test")

add_library(Stack STATIC "${STACK_SRC_DIR}/Stack.cpp")

target_include_directories(Stack PUBLIC
                            "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(Stack PUBLIC
                            "../../include")

if (TEST_ENABLED)
    project(StackTests)

    add_executable(StackTests "${STACK_TEST_DIR}/StackTest.cpp" "${STACK_SRC_DIR}/Stack.cpp")

    target_include_directories(StackTests PUBLIC
                            "${CMAKE_CURRENT_SOURCE_DIR}/include")
    include(FetchContent)
    FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
    )
        # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    target_link_libraries(StackTests gtest_main)
endif()