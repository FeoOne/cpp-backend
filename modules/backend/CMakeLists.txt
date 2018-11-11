set(PROJECT_NAME backend)

message(STATUS "Configure ${PROJECT_NAME}...")

project(${PROJECT_NAME} VERSION ${WORKSPACE_VERSION_FULL} LANGUAGES CXX)

find_package(GMP REQUIRED)
find_package(CURL REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.h")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

add_dependencies(${PROJECT_NAME} engine pmp)

enable_cxx17(${PROJECT_NAME})
setup_compiler_flags(${PROJECT_NAME})

set(libbtc_SOURCE_DIRS ${CMAKE_SOURCE_DIR}/external/libbtc/include)
set(libbtc_LIBRARIES ${CMAKE_SOURCE_DIR}/external/libbtc/.libs/libbtc.a)

set(libsecp256k1_SOURCE_DIRS ${CMAKE_SOURCE_DIR}/external/libbtc/src/secp256k1/include)
set(libsecp256k1_LIBRARIES ${CMAKE_SOURCE_DIR}/external/libbtc/src/secp256k1/.libs/libsecp256k1.a)

# include directories

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        engine
        pmp
        ${GMP_INCLUDES}
        ${CURL_INCLUDE_DIR}
        ${libbtc_SOURCE_DIRS}
        ${libsecp256k1_SOURCE_DIRS}
        ${CMAKE_SOURCE_DIR}/message/generated
        )

# libraries

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        engine
        pmp
        ${GMP_LIBRARIES}
        ${CURL_LIBRARIES}
        ${libbtc_LIBRARIES}
        ${libsecp256k1_LIBRARIES}
        )
