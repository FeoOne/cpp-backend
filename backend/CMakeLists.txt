set(PROJECT_NAME backend)

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

find_package(config REQUIRED)
find_package(soup REQUIRED)
find_package(uv REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

enable_cxx17(${PROJECT_NAME})
setup_compile_options(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${engine_SOURCE_DIR}/src
            ${framework_SOURCE_DIR}/src
            ${Config_INCLUDE_DIR}
            ${GIO_INCLUDE_DIRS}
            ${GLib_INCLUDE_DIRS}
            ${GObject_INCLUDE_DIRS}
            ${Soup_INCLUDE_DIRS}
            ${FLATBUFFERS_INCLUDE_DIR}
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${Config_LIBRARIES}
            ${GIO_LIBRARY}
            ${GLib_LIBRARY}
            ${GObject_LIBRARY}
            ${Soup_LIBRARY}
            framework
            engine
        )
