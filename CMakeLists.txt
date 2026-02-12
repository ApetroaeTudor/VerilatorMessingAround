cmake_minimum_required(VERSION 3.15)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(arm_stuff LANGUAGES CXX)

find_package(verilator REQUIRED)

set(PRJ_NAME simulation)
set(ARM_SC_SRC ${PROJECT_SOURCE_DIR}/arm_SingleCycle/src)
set(ARM_SC_TB ${PROJECT_SOURCE_DIR}/arm_SingleCycle/tbs)

add_executable(${PRJ_NAME} ${ARM_SC_TB}/pc_tb.cpp)
target_compile_definitions(${PRJ_NAME} PRIVATE PRJ_ROOT="${PROJECT_SOURCE_DIR}")

verilate(
    ${PRJ_NAME}
    SOURCES ${ARM_SC_SRC}/DataPath/pc.sv
    TRACE_FST
    OPT_SLOW -Wall -Wpedantic
    DIRECTORY ${PROJECT_SOURCE_DIR}/sim_dir
    THREADS 8
)
