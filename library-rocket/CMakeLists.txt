set(PROJECT_NAME rocket)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

find_package(Config REQUIRED)
find_package(GLib REQUIRED)
find_package(Soup REQUIRED)
find_package(UV REQUIRED)
find_package(PQ REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} src/work/work_context.cpp src/work/work_context.h)

enable_cxx17(${PROJECT_NAME})
setup_compiler_flags(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

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
            ${Config_LIBRARIES}
            ${GObject_LIBRARY}
            ${UUID_LIBRARIES}
            ${GLib_LIBRARY}
            ${Soup_LIBRARY}
            ${UV_LIBRARIES}
            ${PQ_LIBRARIES}
            ${GIO_LIBRARY}
            groot
        )
