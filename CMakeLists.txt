cmake_minimum_required(VERSION 3.10)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
        ${CMAKE_SOURCE_DIR}/CMakeModules
        )

add_subdirectory(framework)
add_subdirectory(engine)
add_subdirectory(backend)
