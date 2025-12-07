cmake_minimum_required(VERSION 3.10)

# Project configuration for server (dummy config for Raspberry Pi)
project(server)

# C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Determine if building independently or as subdirectory
# If CMAKE_SOURCE_DIR == CMAKE_CURRENT_SOURCE_DIR, we're building independently
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    # Independent build: outputs go to build/bin within server directory
    set(OUTPUT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
else()
    # Building from root: outputs go to server/build/bin
    set(OUTPUT_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BASE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_BASE_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_BASE_DIR}/lib)

# Source files
set(SERVER_SOURCES
    main.cpp
    App/App.cpp
)

# Include directories
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# Create executable
add_executable(server ${SERVER_SOURCES})

# Set output name
set_target_properties(server PROPERTIES
    OUTPUT_NAME "server"
    RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_BASE_DIR}/bin
)

