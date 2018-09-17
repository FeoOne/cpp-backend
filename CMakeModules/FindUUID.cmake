find_path(UUID_INCLUDE_DIR NAMES ossp/uuid.h)
find_library(UUID_LIBRARIES NAMES libuuid.dylib libuuid.so)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(UUID DEFAULT_MSG UUID_LIBRARIES UUID_INCLUDE_DIR)

if(UUID_INCLUDE_DIR AND UUID_LIBRARIES)
    SET(UUID_FOUND TRUE)
else()
    SET(UUID_FOUND FALSE)
endif()

if (UUID_FOUND)
    message(STATUS "Found libuuid: ${UUID_LIBRARIES}, ${UUID_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Couldn't find libuuid.")
endif()

mark_as_advanced(UUID_LIBRARIES UUID_INCLUDE_DIR)
