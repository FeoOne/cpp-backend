set(PROJECT_NAME stl)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/main/stl_consts_gen.h.in
        ${CMAKE_CURRENT_SOURCE_DIR}/src/main/stl_consts_gen.h
        )

find_package(CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(GLIB REQUIRED)
find_package(UUID REQUIRED)
find_package(UV REQUIRED)
find_package(OPENSSL REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

enable_cxx17(${PROJECT_NAME})
setup_compiler_flags(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

# jemalloc config

set(Jemalloc_SOURCE_DIRS ${CMAKE_SOURCE_DIR}/3rdparty/jemalloc/include)
set(Jemalloc_LIBRARIES ${CMAKE_SOURCE_DIR}/3rdparty/jemalloc/lib/libjemalloc.a)

# include directories

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${Jemalloc_SOURCE_DIRS}
        ${Config_INCLUDE_DIR}
        ${ZLIB_INCLUDE_DIRS}
        ${UUID_INCLUDE_DIR}
        ${GLib_INCLUDE_DIRS}
        ${UV_INCLUDE_DIRS}
        ${OPENSSL_INCLUDE_DIR}
        )

# libraries

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        ${Jemalloc_LIBRARIES}
        ${Config_LIBRARIES}
        ${ZLIB_LIBRARIES}
        ${UUID_LIBRARIES}
        ${GLib_LIBRARY}
        ${UV_LIBRARIES}
        ${OPENSSL_LIBRARIES}
        )
