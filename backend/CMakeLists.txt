cmake_minimum_required(VERSION 3.16)

project(backend)

find_package(Clang CONFIG REQUIRED)

file(GLOB_RECURSE SRC_FILES "*.h" "*.hpp" "*.cpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
add_library(backend SHARED ${SRC_FILES})
target_include_directories(backend PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(backend PRIVATE ${CLANG_INCLUDE_DIRS})
target_link_libraries(backend PRIVATE clangTooling nlohmann_json)

if (DEFINED CMAKE_OBJCOPY)
    install(CODE "execute_process(
        COMMAND ${CMAKE_OBJCOPY} --only-keep-debug libbackend.so libbackend.so.dbg
        COMMAND ${CMAKE_OBJCOPY} --strip-debug --strip-unneeded libbackend.so
        WORKING_DIRECTORY ${CMAKE_LIBRARY_OUTPUT_DIRECTORY})"
    )
    install(FILES ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/libbackend.so.dbg
        DESTINATION dbg
    )
endif()
install(TARGETS backend
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
    RUNTIME DESTINATION bin
)
if(WIN32)
    install(FILES $<TARGET_PDB_FILE:backend> DESTINATION pdb OPTIONAL)
endif(WIN32)

# for cli
add_library(backend_STATIC STATIC ${SRC_FILES})
target_include_directories(backend_STATIC PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(backend_STATIC PUBLIC ${CLANG_INCLUDE_DIRS})
target_link_libraries(backend_STATIC PUBLIC clangTooling nlohmann_json)
target_compile_definitions(backend_STATIC PUBLIC backend_STATIC)
