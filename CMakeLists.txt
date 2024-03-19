cmake_minimum_required(VERSION 3.15)

set(EMULATOR_SRC_DIR "src")
set(EMULATOR_INCLUDE_DIR "include")

set(EMULATOR_INPUT_DIR "Programms")
set(EMULATOR_OUTPUT_DIR "Output")

configure_file(IO_dirs.hpp.in IO_dirs.hpp)

project(Emulator)

add_subdirectory("libs/Stack")

add_executable(Emulator "${EMULATOR_SRC_DIR}/main.cpp"
                        "${EMULATOR_SRC_DIR}/Emulator.cpp"
                        "${EMULATOR_SRC_DIR}/commands.cpp")

target_include_directories(Emulator PUBLIC "${PROJECT_BINARY_DIR}")

target_include_directories(Emulator PUBLIC "${EMULATOR_INCLUDE_DIR}")

target_link_libraries(Emulator PRIVATE Stack)


# add_executable(StackTest "test/StackTest.cpp")

# target_link_libraries(StackTest gtest_main)

# # Google tests
# enable_testing()

# include(FetchContent)
# FetchContent_Declare(
#         googletest
#         URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )

# # For Windows: Prevent overriding the parent project's compiler/linker settings
# set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# FetchContent_MakeAvailable(googletest)   