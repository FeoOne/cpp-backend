cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

cmake_policy(SET CMP0048 NEW)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/CMakeModules
        )

include(${CMAKE_SOURCE_DIR}/CMakeTools/Compiler.cmake)
include(${CMAKE_SOURCE_DIR}/CMakeTools/Version.cmake)

setup_version()

add_subdirectory(framework)
add_subdirectory(engine)
add_subdirectory(backend)
add_subdirectory(thanos)
