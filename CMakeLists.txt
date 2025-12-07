cmake_minimum_required(VERSION 3.10)
project(raspi-ic)

# Set default build type to Release if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Build both client and server
add_subdirectory(server)
add_subdirectory(client)

