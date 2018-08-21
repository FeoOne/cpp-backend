set(PROJECT_NAME rocket)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

find_package(NLOHMANJSON REQUIRED)
find_package(CONFIG REQUIRED)
find_package(GLIB REQUIRED)
find_package(SOUP REQUIRED)
find_package(UV REQUIRED)
find_package(PQ REQUIRED)
find_package(flatbuffers REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} src/work/work_context.cpp src/work/work_context.h)

enable_cxx17(${PROJECT_NAME})
setup_compile_options(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${groot_SOURCE_DIR}/src
            ${NlohmanJson_INCLUDE_DIR}
            ${Config_INCLUDE_DIR}
            ${GIO_INCLUDE_DIRS}
            ${GLib_INCLUDE_DIRS}
            ${GObject_INCLUDE_DIRS}
            ${Soup_INCLUDE_DIRS}
            ${UV_INCLUDE_DIRS}
            ${FLATBUFFERS_INCLUDE_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${Config_LIBRARIES}
            ${GIO_LIBRARY}
            ${GLib_LIBRARY}
            ${GObject_LIBRARY}
            ${Soup_LIBRARY}
            ${UV_LIBRARIES}
            groot
        )
