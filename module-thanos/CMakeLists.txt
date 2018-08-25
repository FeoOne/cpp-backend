set(PROJECT_NAME thanos)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

find_package(NlohmanJson REQUIRED)
find_package(Config REQUIRED)
find_package(GLib REQUIRED)
find_package(Soup REQUIRED)
find_package(UV REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

enable_cxx17(${PROJECT_NAME})
setup_compile_options(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${rocket_SOURCE_DIR}/src
            ${groot_SOURCE_DIR}/src
            ${NlohmanJson_INCLUDE_DIR}
            ${Config_INCLUDE_DIR}
            ${GIO_INCLUDE_DIRS}
            ${GLib_INCLUDE_DIRS}
            ${GObject_INCLUDE_DIRS}
            ${Soup_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${Config_LIBRARIES}
            ${GIO_LIBRARY}
            ${GLib_LIBRARY}
            ${GObject_LIBRARY}
            ${Soup_LIBRARY}
            groot
            rocket
        )
