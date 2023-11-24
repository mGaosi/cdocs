cmake_minimum_required(VERSION 3.16)

project(cli)

file(GLOB_RECURSE SRC_FILES "*.h" "*.hpp" "*.cpp")
source_group(TREE ${CMAKE_CURRENT_SOURCE_DIR} FILES ${SRC_FILES})
add_executable(cdocs ${SRC_FILES})
target_include_directories(cdocs PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(cdocs PRIVATE backend_STATIC nlohmann_json)

install(TARGETS cdocs
    RUNTIME DESTINATION tools/
)
if(WIN32)
    install(FILES $<TARGET_PDB_FILE:cdocs> DESTINATION pdb OPTIONAL)
endif(WIN32)
