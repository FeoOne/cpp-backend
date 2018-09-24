find_path(Config_INCLUDE_DIR NAMES libconfig.h)
find_library(Config_LIBRARIES NAMES libconfig.dylib libconfig.so)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CONFIG DEFAULT_MSG Config_LIBRARIES Config_INCLUDE_DIR)

if(Config_INCLUDE_DIR AND Config_LIBRARIES)
    SET(CONFIG_FOUND TRUE)
else()
    SET(CONFIG_FOUND FALSE)
endif()

if (NOT CONFIG_FOUND)
    message(FATAL_ERROR "Couldn't find libconfig.")
endif()

mark_as_advanced(Config_LIBRARIES Config_INCLUDE_DIR)
