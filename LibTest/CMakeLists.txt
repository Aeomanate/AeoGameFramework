cmake_minimum_required(VERSION 3.13)
project(LibTest)

set(CMAKE_CXX_FLAGS
    "${CMAKE_CXX_FLAGS} \
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
        \
    "
    )

set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc")

set(BUILD_DIR ${CMAKE_CURRENT_SOURCE_DIR}/Build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BUILD_DIR})

set(AEOLIB_ROOT "D:/Programms/ProgrammingEnvironment/Librares/AeoGameLib")
set(AEO_DLL ${AEOLIB_ROOT}/bin/libAeoGameFramework.dll)
include_directories(${AEOLIB_ROOT}/include)

add_executable(${PROJECT_NAME}
    main.cpp

    )

target_link_libraries(${PROJECT_NAME} ${AEO_DLL})

install(FILES ${AEO_DLL} DESTINATION ${BUILD_DIR})
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${BUILD_DIR})











