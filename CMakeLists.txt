cmake_minimum_required(VERSION 3.20)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
#rpath
if(UNIX)
    if(APPLE)
        set(CMAKE_MACOSX_RPATH ON)
    else()
        set(CMAKE_INSTALL_RPATH "$ORIGIN")
    endif()
    set(CMAKE_CXX_VISIBILITY_PRESET hidden)
    set(CMAKE_C_VISIBILITY_PRESET hidden)
endif()

project(cdocs)

if (WIN32)
    add_compile_definitions(WIN32_LEAN_AND_MEAN NOMINMAX)
endif()

if(MSVC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MP")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
    add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:/Zc:__cplusplus>)
    add_compile_options($<$<COMPILE_LANGUAGE:C,CXX>:/std:c++17>)
endif(MSVC)

set(CMAKE_CXX_STANDARD 17) #-stdc++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON) #-fPIC
set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(third)
add_subdirectory(backend)
add_subdirectory(cli)
