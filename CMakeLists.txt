cmake_minimum_required(VERSION 3.25)
project(AeoGameFramework VERSION 1.1 LANGUAGES CXX)

if(POLICY CMP0207)
    cmake_policy(SET CMP0207 NEW)
endif()

# Standalone installation packages only LibTest and its runtime dependencies.
if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_INSTALL_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/LibTest/installed"
            CACHE PATH "Installation directory for LibTest" FORCE
    )
endif()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Dependencies
include(FetchContent)

set(BUILD_SHARED_LIBS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(SFML_BUILD_AUDIO OFF CACHE BOOL "Build SFML audio")
set(SFML_BUILD_NETWORK OFF CACHE BOOL "Build SFML network")

FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.2
        SYSTEM
)
FetchContent_MakeAvailable(SFML)

# Keep SFML's SDK out of the test installation. Linked targets still build.
set_property(DIRECTORY "${sfml_SOURCE_DIR}" PROPERTY EXCLUDE_FROM_ALL TRUE)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Library targets
set(SRC_FRAMEWORK
        src/AeoGameFramework.cpp
        src/Timer.cpp
        src/Sprite.cpp
        src/AlSpriteImpl.cpp
        src/AlSpriteImpl.hpp
        src/Internal.cpp
        src/Internal.hpp
)

add_library(AeoGameFramework_shared SHARED ${SRC_FRAMEWORK})
add_library(AeoGameFramework_static STATIC ${SRC_FRAMEWORK})

add_library(Aeo::GameFramework::Shared ALIAS AeoGameFramework_shared)
add_library(Aeo::GameFramework::Static ALIAS AeoGameFramework_static)

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# The public header uses this definition to disable DLL import/export.
target_compile_definitions(AeoGameFramework_static PUBLIC AEO_STATIC)

foreach(target IN ITEMS AeoGameFramework_shared AeoGameFramework_static)
    set_target_properties(${target} PROPERTIES VERSION "${PROJECT_VERSION}")

    if(NOT PROJECT_IS_TOP_LEVEL)
        set_target_properties(${target} PROPERTIES EXCLUDE_FROM_ALL TRUE)
    endif()

    target_compile_features(${target} PUBLIC cxx_std_20)

    target_include_directories(${target} PUBLIC
            "${CMAKE_CURRENT_SOURCE_DIR}/include"
    )

    target_compile_definitions(${target} PRIVATE FRAMEWORK_PROJECT)

    target_link_libraries(${target} PRIVATE
            sfml-graphics sfml-window sfml-system
    )

    if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        target_compile_options(${target} PRIVATE
                -pedantic -Wall -Wextra
                -Wconversion -Wenum-compare -Wfloat-equal
                -Woverloaded-virtual
        )
    endif()
endforeach()

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# Tests are built and installed only when opening this project directly.
if(PROJECT_IS_TOP_LEVEL)
    add_subdirectory(LibTest)
endif()
