set(PROJECT_NAME thanos)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME} rocket)

enable_cxx17(${PROJECT_NAME})
setup_compiler_flags(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        rocket
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        rocket
        )
