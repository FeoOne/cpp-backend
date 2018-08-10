set(PROJECT_NAME backend)

get_property(PROJECT_VERSION GLOBAL PROPERTY VERSION)
project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES CXX)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

enable_cxx17(${PROJECT_NAME})
setup_compile_options(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${framework_SOURCE_DIR}/src
            ${engine_SOURCE_DIR}/src
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            framework
            engine
        )
