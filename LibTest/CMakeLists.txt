# This directory is added by the framework's root CMakeLists.txt.
foreach(variant IN ITEMS Shared Static)
    set(test_target LibTest_${variant})

    add_executable(${test_target} main.cpp)

    target_link_libraries(${test_target} PRIVATE
            Aeo::GameFramework::${variant}
    )

    # Embed MinGW runtimes in the fully static test executable.
    if(MINGW AND CMAKE_CXX_COMPILER_ID STREQUAL "GNU"
            AND variant STREQUAL "Static")
        target_link_options(${test_target} PRIVATE -static)
    endif()

    if(WIN32 AND variant STREQUAL "Shared")
        # Allow launching the shared test from the build directory.
        add_custom_command(TARGET ${test_target} POST_BUILD
                COMMAND "${CMAKE_COMMAND}" -E copy_if_different
                $<TARGET_RUNTIME_DLLS:${test_target}>
                "$<TARGET_FILE_DIR:${test_target}>"
                COMMAND_EXPAND_LISTS
                VERBATIM
        )
    endif()
endforeach()

if(WIN32)
    # Scan both the executable and framework DLL for compiler/runtime DLLs.
    get_filename_component(compiler_runtime_dir "${CMAKE_CXX_COMPILER}" DIRECTORY)

    install(TARGETS LibTest_Shared AeoGameFramework_shared
            RUNTIME_DEPENDENCIES
            DIRECTORIES "${compiler_runtime_dir}"
            PRE_EXCLUDE_REGEXES
            "^[Aa][Pp][Ii]-[Mm][Ss]-.*"
            "^[Ee][Xx][Tt]-[Mm][Ss]-.*"
            POST_EXCLUDE_REGEXES
            ".*[/\\\\][Ww][Ii][Nn][Dd][Oo][Ww][Ss][/\\\\].*"
            RUNTIME DESTINATION bin
    )

    install(TARGETS LibTest_Static
            RUNTIME DESTINATION bin
    )
else()
    # Keep the shared test runnable from the installed layout on Unix.
    if(APPLE)
        set_target_properties(LibTest_Shared PROPERTIES
                INSTALL_RPATH "@loader_path/../lib"
        )
    elseif(UNIX)
        set_target_properties(LibTest_Shared PROPERTIES
                INSTALL_RPATH "$ORIGIN/../lib"
        )
    endif()

    install(TARGETS LibTest_Shared LibTest_Static AeoGameFramework_shared
            RUNTIME DESTINATION bin
            LIBRARY DESTINATION lib
    )
endif()
