cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/CMakeModules
        )

include(${CMAKE_SOURCE_DIR}/CMakeTools/Compiler.cmake)

set_property(GLOBAL PROPERTY PROJECT_VERSION "0.0.1")

add_subdirectory(framework)
add_subdirectory(engine)
add_subdirectory(backend)
