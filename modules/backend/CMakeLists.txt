set(PROJECT_NAME backend)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME} engine pmp)

enable_cxx17(${PROJECT_NAME})
setup_compiler_flags(${PROJECT_NAME})

# include directories

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        engine
        pmp
        ${CMAKE_SOURCE_DIR}/message/src
        ${CMAKE_SOURCE_DIR}/message/generated
        )

# libraries

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        engine
        pmp
        )
