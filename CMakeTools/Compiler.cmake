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
        target_link_libraries(${TARGET} PRIVATE pthread)
    endif()
endfunction(enable_cxx17)

function(setup_compile_options TARGET)
    target_compile_options(${TARGET} PRIVATE
            -Wall
            -Wextra
            -Weverything
            -Wno-padded
            -Wno-return-type
            -Wno-c++98-compat
            -Wno-weak-vtables
            -Wno-documentation
            -Wno-old-style-cast
            -Wno-unused-parameter
            -Wno-reserved-id-macro
            -Wno-format-nonliteral
            -Wno-global-constructors
            -Wno-exit-time-destructors
            -Wno-c++98-compat-pedantic
            -Wno-c++98-c++11-c++14-compat
            -Wno-zero-as-null-pointer-constant
            -Wno-documentation-unknown-command
            -Wno-c++98-c++11-c++14-compat-pedantic
            -Wno-gnu-zero-variadic-macro-arguments
            )
endfunction(setup_compile_options)
