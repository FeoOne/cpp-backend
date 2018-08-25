set(PROJECT_NAME groot)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/main/groot_consts_gen.h.in
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/groot_consts_gen.h
        )

find_package(NlohmanJson REQUIRED)
find_package(Config REQUIRED)
find_package(GLib REQUIRED)
find_package(UUID REQUIRED)
find_package(UV REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

enable_cxx17(${PROJECT_NAME})
setup_compile_options(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${CMAKE_CURRENT_SOURCE_DIR}/src
            ${NlohmanJson_INCLUDE_DIR}
            ${Config_INCLUDE_DIR}
            ${GLib_INCLUDE_DIRS}
            #${UUID_INCLUDE_DIR}
            ${UV_INCLUDE_DIRS}
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${Config_LIBRARIES}
            ${UUID_LIBRARIES}
            ${GLib_LIBRARY}
            ${UV_LIBRARIES}
        )
