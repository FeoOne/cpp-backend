set(PROJECT_NAME engine)

get_property(PROJECT_VERSION GLOBAL PROPERTY VERSION)
project(${PROJECT_NAME} VERSION ${VERSION} LANGUAGES CXX)

find_package(config REQUIRED)
find_package(soup REQUIRED)
find_package(uv REQUIRED)
find_package(flatbuffers REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

enable_cxx17(${PROJECT_NAME})
setup_compile_options(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${Config_INCLUDE_DIR}
            ${GIO_INCLUDE_DIRS}
            ${GLib_INCLUDE_DIRS}
            ${GObject_INCLUDE_DIRS}
            ${Soup_INCLUDE_DIRS}
            ${UV_INCLUDE_DIRS}
            ${FLATBUFFERS_INCLUDE_DIR}
            ${framework_SOURCE_DIR}/src
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${Config_LIBRARIES}
            ${GIO_LIBRARY}
            ${GLib_LIBRARY}
            ${GObject_LIBRARY}
            ${Soup_LIBRARY}
            ${UV_LIBRARIES}
            framework
        )
