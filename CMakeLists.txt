#[=[
CMake configuration for general stm32 black pill use
# By Justsomedudes
# 3 March 2026
]=]

cmake_minimum_required(VERSION 3.20)
# include cmake macros
include(${CMAKE_SOURCE_DIR}/cmake/gcc-arm-none-eabi.cmake)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(CMAKE_PROJECT_NAME stm32_printer_v0_1)

# Project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})
enable_language(C ASM)

# Grab all files from folder
file(GLOB MAIN_SRC src/*.c src/*.cpp)
file(GLOB_RECURSE LIB_SRC libraries/*.c)

# Generate .elf files
add_executable(${CMAKE_PROJECT_NAME}
    ${MAIN_SRC}
    ${LIB_SRC}
    ${CMAKE_SOURCE_DIR}/startup_stm32f411xe.s
)

# Include directories
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/inc
    ${CMAKE_SOURCE_DIR}/libraries
    ${CMAKE_SOURCE_DIR}/libraries/CMSIS
    ${CMAKE_SOURCE_DIR}/libraries/CMSIS/Include
    ${CMAKE_SOURCE_DIR}/libraries/CMSIS/Device/ST/STM32F4xx/Include
    ${CMAKE_SOURCE_DIR}/libraries/STM32F4xx_HAL_Driver/Inc
)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE
    USE_HAL_DRIVER
    STM32F411xE
    $<$<CONFIG:Debug>:DEBUG>
)

set(MCU_FLAGS
    -mcpu=cortex-m4
    -mthumb
    -ffunction-sections
    -fdata-sections
    -Wall
    -Wextra
    -Wno-unused-parameter
)

target_compile_options(${CMAKE_PROJECT_NAME} PRIVATE ${MCU_FLAGS})
target_link_options(${CMAKE_PROJECT_NAME} PRIVATE ${MCU_FLAGS})

add_custom_target(flash
    COMMAND C:/xpack-openocd/bin/openocd.exe
        -f interface/stlink.cfg
        -f target/stm32f4x.cfg
        -c "program ${CMAKE_PROJECT_NAME}.elf verify reset exit"
    DEPENDS ${CMAKE_PROJECT_NAME}
)