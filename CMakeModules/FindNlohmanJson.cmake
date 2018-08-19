find_path(NlohmanJson_INCLUDE_DIR NAMES nlohmann/json.hpp)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NLOHMANJSON DEFAULT_MSG NlohmanJson_INCLUDE_DIR)

if(NlohmanJson_INCLUDE_DIR)
    SET(NLOHMANJSON_FOUND TRUE)
else()
    SET(NLOHMANJSON_FOUND FALSE)
endif()

if (NLOHMANJSON_FOUND)
    message(STATUS "Found nlohman json: ${NlohmanJson_INCLUDE_DIR}")
else()
    message(FATAL_ERROR "Couldn't find nlohman json.")
endif()

mark_as_advanced(NlohmanJson_INCLUDE_DIR)
