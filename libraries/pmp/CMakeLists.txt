set(PROJECT_NAME pmp)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME} stl)

enable_cxx17(${PROJECT_NAME})
setup_compiler_flags(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

# include directories

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        stl
        )

# libraries

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        stl
        )
