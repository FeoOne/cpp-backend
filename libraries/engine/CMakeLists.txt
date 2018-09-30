set(PROJECT_NAME engine)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

find_package(Soup REQUIRED)
find_package(PQ REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME} stl)

enable_cxx17(${PROJECT_NAME})
setup_compiler_flags(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

# include directories

target_include_directories(${PROJECT_NAME}
        PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        stl
        ${GObject_INCLUDE_DIRS}
        ${Soup_INCLUDE_DIRS}
        ${GIO_INCLUDE_DIRS}
        ${PQ_INCLUDE_DIR}
        )

# libraries

target_link_libraries(${PROJECT_NAME}
        PUBLIC
        stl
        ${GObject_LIBRARY}
        ${Soup_LIBRARY}
        ${PQ_LIBRARIES}
        ${GIO_LIBRARY}
        )
