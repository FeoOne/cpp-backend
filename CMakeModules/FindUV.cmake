find_path(UV_INCLUDE_DIR NAMES uv.h)
find_library(UV_LIBRARIES NAMES uv libuv)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UV DEFAULT_MSG UV_LIBRARIES UV_INCLUDE_DIR)

if(UV_INCLUDE_DIR AND UV_LIBRARIES)
    SET(UV_FOUND TRUE)
else()
    SET(UV_FOUND FALSE)
endif()

if (UV_FOUND)
    message(STATUS "Found libuv: ${UV_LIBRARIES}, ${UV_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Couldn't find libuv.")
endif()
