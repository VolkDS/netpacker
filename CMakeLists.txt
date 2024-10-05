cmake_minimum_required(VERSION 3.14)

project(netpacker LANGUAGES CXX)

## Find libraries ##############################################################
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
set(CMAKE_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_INCLUDE_PATH})

option(NETPACKER_BUILD_EXAMPLES "Build examples" OFF)
option(NETPACKER_BUILD_TESTS "Build tests" OFF)

## Find out build type #########################################################
set(CMAKE_CONFIGURATION_TYPES Debug Release)
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

message("Current configuration type: ${CMAKE_BUILD_TYPE}")

include(GetModuleVersion)
include(CompileSettings)
include(MakeVersionFile)
create_version_file(version.h.in ${CMAKE_CURRENT_BINARY_DIR}/include/netpacker/version.h)

add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)

### Include Directories ###
target_include_directories(${PROJECT_NAME}
    INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
)

## Examples ####################################################################
if (NETPACKER_BUILD_EXAMPLES)
    message(STATUS "Building of examples is enabled")
    add_subdirectory(examples)
endif()

## Tests #######################################################################
if (NETPACKER_BUILD_TESTS)
    message(STATUS "Building of tests is enabled")
    enable_testing()
    add_subdirectory(tests)
endif()
