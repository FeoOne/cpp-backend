find_path(JsonCpp_INCLUDE_DIR NAMES json/json.h)
find_library(JsonCpp_LIBRARIES NAMES libjsoncpp.dylib libjsoncpp.so)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(JSONCPP DEFAULT_MSG JsonCpp_LIBRARIES JsonCpp_INCLUDE_DIR)

if(JsonCpp_INCLUDE_DIR AND JsonCpp_LIBRARIES)
    SET(JsonCpp_FOUND TRUE)
else()
    SET(JsonCpp_FOUND FALSE)
endif()

if (NOT JsonCpp_FOUND)
    message(FATAL_ERROR "Couldn't find jsoncpp.")
endif()

mark_as_advanced(JsonCpp_LIBRARIES JsonCpp_INCLUDE_DIR)
