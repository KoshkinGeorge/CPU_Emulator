cmake_minimum_required(VERSION 3.15)

set(EMULATOR_SRC_DIR "src")
set(EMULATOR_INCLUDE_DIR "include")

set(EMULATOR_INPUT_DIR "Programms")
set(EMULATOR_OUTPUT_DIR "Output")
set(EMULATOR_PROCESSED_DIR "Processed")

configure_file(IO_dirs.hpp.in IO_dirs.hpp)

project(Emulator)

add_subdirectory("libs/Stack")

add_executable(Emulator "${EMULATOR_SRC_DIR}/main.cpp"
                        "${EMULATOR_SRC_DIR}/Emulator.cpp"
                        "${EMULATOR_SRC_DIR}/commands.cpp"
                        "${EMULATOR_SRC_DIR}/Preprocessor.cpp"
                        "${EMULATOR_SRC_DIR}/my_funcs.cpp")

target_include_directories(Emulator PUBLIC "${PROJECT_BINARY_DIR}")

target_include_directories(Emulator PUBLIC "${EMULATOR_INCLUDE_DIR}")

target_link_libraries(Emulator PRIVATE Stack)