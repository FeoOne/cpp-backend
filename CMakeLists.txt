cmake_minimum_required(VERSION 3.12 FATAL_ERROR)

cmake_policy(SET CMP0048 NEW)

set(WORKSPACE_NAME bitpayments)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/CMakeModules
        )

include(${CMAKE_SOURCE_DIR}/CMakeTools/Compiler.cmake)
include(${CMAKE_SOURCE_DIR}/CMakeTools/Version.cmake)

setup_version()

# framework
add_subdirectory(library-groot)

# engine
add_subdirectory(library-rocket)

# shared constants
add_subdirectory(library-mantis)

# db operator
add_subdirectory(module-strange)

# web backend
add_subdirectory(module-quill)

# bitcoin blockchain
add_subdirectory(module-thanos)
