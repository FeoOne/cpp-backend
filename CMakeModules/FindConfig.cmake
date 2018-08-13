find_path(Config_INCLUDE_DIR NAMES libconfig.h)
find_library(Config_LIBRARIES NAMES libconfig.dylib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CONFIG DEFAULT_MSG Config_LIBRARIES Config_INCLUDE_DIR)

if(Config_INCLUDE_DIR AND Config_LIBRARIES)
    SET(CONFIG_FOUND TRUE)
else()
    SET(CONFIG_FOUND FALSE)
endif()

if (CONFIG_FOUND)
    message(STATUS "Found libconfig: ${Config_LIBRARIES}, ${Config_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Couldn't find libconfig.")
endif()
