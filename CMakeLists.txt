cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(verilator_demo LANGUAGES CXX)

find_package(verilator REQUIRED)
set(PRJ_NAME simulation)

add_executable(${PRJ_NAME} test_tb.cpp)

verilate(
    ${PRJ_NAME}
    SOURCES test.sv
    TRACE_FST
    OPT_SLOW -Wall -Wpedantic
    DIRECTORY ${PROJECT_SOURCE_DIR}/sim_dir
    THREADS 8
)
