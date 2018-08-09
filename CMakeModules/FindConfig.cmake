find_path(CONFIG_INCLUDE_DIR NAMES libconfig.h)
find_library(CONFIG_LIBRARIES NAMES libconfig)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CONFIG DEFAULT_MSG CONFIG_LIBRARIES CONFIG_INCLUDE_DIR)

if(CONFIG_INCLUDE_DIR AND CONFIG_LIBRARIES)
    SET(CONFIG_FOUND TRUE)
else()
    SET(CONFIG_FOUND FALSE)
endif()

if (CONFIG_FOUND)
    message(STATUS "Found libconfig: ${CONFIG_LIBRARIES}, ${CONFIG_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Couldn't find libconfig.")
endif()
