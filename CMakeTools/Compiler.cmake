function(enable_cxx17 TARGET)
    target_compile_features(${TARGET} PUBLIC cxx_std_17)
    set_target_properties(${TARGET} PROPERTIES
            CXX_STANDARD 17
            CXX_STANDARD_REQUIRED ON
            )
    if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
        set_target_properties(${TARGET} PROPERTIES COMPILE_FLAGS "/std:c++latest")
    elseif (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set_target_properties(${TARGET} PROPERTIES
                COMPILE_FLAGS "-stdlib=libc++ -pthread"
                )
        target_link_libraries(${TARGET} PRIVATE c++experimental pthread)
    endif()
endfunction(enable_cxx17)

function(setup_compile_options TARGET)
    target_compile_options(${TARGET} PRIVATE
            -Wall
            -Wextra
            -Weverything
            -Wno-c++98-compat
            -Wno-c++98-c++11-c++14-compat
            -Wno-exit-time-destructors
            -Wno-weak-vtables
            -Wno-global-constructors
            -Wno-c++98-compat-pedantic
            -Wno-gnu-zero-variadic-macro-arguments
            )
endfunction()
