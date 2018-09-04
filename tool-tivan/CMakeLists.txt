set(PROJECT_NAME tivan)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

enable_cxx17(${PROJECT_NAME})
setup_compiler_flags(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${groot_SOURCE_DIR}/src
        ${Config_INCLUDE_DIR}
        ${UUID_INCLUDE_DIR}
        ${GIO_INCLUDE_DIRS}
        ${GLib_INCLUDE_DIRS}
        ${GObject_INCLUDE_DIRS}
        ${Soup_INCLUDE_DIRS}
        ${UV_INCLUDE_DIRS}
        ${PQ_INCLUDE_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        groot
        ${GIO_LIBRARY}
        ${GLib_LIBRARY}
        ${GObject_LIBRARY}
        )
