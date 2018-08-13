set(PROJECT_NAME framework)

#get_property(PROJECT_VERSION GLOBAL PROPERTY VERSION)
project(${PROJECT_NAME} VERSION ${PROJECT_VERSION} LANGUAGES CXX)

find_package(config REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})

enable_cxx17(${PROJECT_NAME})
setup_compile_options(${PROJECT_NAME})

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${VERSION} SOVERSION ${VERSION})

target_include_directories(${PROJECT_NAME}
        PRIVATE
            ${Config_INCLUDE_DIR}
            ${CMAKE_CURRENT_SOURCE_DIR}/src
        )

target_link_libraries(${PROJECT_NAME}
        PRIVATE
            ${Config_LIBRARIES}
        )
