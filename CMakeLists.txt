cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

cmake_policy(SET CMP0048 NEW)

set(WORKSPACE_NAME bitpayments)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/CMakeModules
        )

include(${CMAKE_SOURCE_DIR}/CMakeTools/Compiler.cmake)
include(${CMAKE_SOURCE_DIR}/CMakeTools/Version.cmake)

setup_version()

add_subdirectory(libraries/stl)
add_subdirectory(libraries/pmp)
add_subdirectory(libraries/engine)

add_subdirectory(modules/backend)
add_subdirectory(modules/database)
add_subdirectory(modules/manbtc)

add_subdirectory(tools/pmgen)
