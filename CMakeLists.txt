cmake_minimum_required(VERSION 3.20)
project(AeoGameFramework)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -std=gnu++2a \
        -pedantic \
        -Wall \
        -Wextra\
         \
        -Wconversion \
        -Wenum-compare \
        -Wfloat-equal \
        -Woverloaded-virtual \
        \
    "
    )


if (CMAKE_BUILD_TYPE EQUAL "RELEASE")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3")
endif()
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

add_definitions(-DFRAMEWORK_PROJECT)

set(SRC_FRAMEWORK
    AeoGameFramework.cpp
    AeoGameFramework.hpp
    Timer.cpp
    Sprite.cpp
    AlSpriteImpl.cpp
    AlSpriteImpl.hpp
    Internal.cpp
    Internal.hpp

    )

set(LIB_HEADER AeoGameFramework.hpp)

add_library(${PROJECT_NAME} SHARED ${SRC_FRAMEWORK})
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0)

set(LIBS_ROOT "D:/Programms/ProgrammingEnvironment/Librares")
set(SFML_ROOT "${LIBS_ROOT}/SFML-2.5.1")
set(SFML_DIR "${SFML_ROOT}/lib/cmake/SFML")
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

set(AEOLIB_DEST "${LIBS_ROOT}/AeoGameLib")
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${AEOLIB_DEST}/bin
        LIBRARY DESTINATION ${AEOLIB_DEST}/lib
        ARCHIVE DESTINATION ${AEOLIB_DEST}/lib)
install(FILES ${LIB_HEADER} DESTINATION ${AEOLIB_DEST}/include)


add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/LibTest)





