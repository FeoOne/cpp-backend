function(setup_version)
    file(READ version.txt LOADED_VERSION)

    string(REGEX MATCH "^[0-9]+.[0-9]+.[0-9]+.[0-9]+$" OUT ${LOADED_VERSION})

    if (OUT STREQUAL "")
        message(FATAL_ERROR "Failed to parse version from version.txt.")
    endif()

    string(REPLACE "." ";" VERSION_LIST ${LOADED_VERSION})

    list(GET VERSION_LIST 0 MAJOR)
    list(GET VERSION_LIST 1 MINOR)
    list(GET VERSION_LIST 2 PATCH)
    list(GET VERSION_LIST 3 BUILD)
    list(REMOVE_AT VERSION_LIST 3)

    if (CMAKE_BUILD_TYPE EQUAL "Release")
        # increase build number for release configuration
        math(EXPR BUILD "${BUILD} + 1")
    endif()

    list(JOIN VERSION_LIST "." FULL_VERSION)

    message(STATUS "Workspace version: ${FULL_VERSION}, build number: ${BUILD}")

    if (CMAKE_BUILD_TYPE EQUAL "Release")
        file(WRITE "version.txt" "${FULL_VERSION}.${BUILD}")
    endif()

    set(WORKSPACE_VERSION_MAJOR ${MAJOR} PARENT_SCOPE)
    set(WORKSPACE_VERSION_MINOR ${MINOR} PARENT_SCOPE)
    set(WORKSPACE_VERSION_PATCH ${PATCH} PARENT_SCOPE)
    set(WORKSPACE_VERSION_BUILD ${BUILD} PARENT_SCOPE)
    set(WORKSPACE_VERSION_FULL ${FULL_VERSION} PARENT_SCOPE)
endfunction()
