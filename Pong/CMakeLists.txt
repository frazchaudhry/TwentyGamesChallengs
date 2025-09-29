cmake_minimum_required(VERSION 3.15...4.11)
project(Pong C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

file(GLOB SOURCES "src/*.cpp")

add_subdirectory(external/LibraC)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_target(copy_shaders ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/shaders
    ${PROJECT_BINARY_DIR}/$<CONFIGURATION>/shaders
    COMMENT "Copying shaders into binary directory")


add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${PROJECT_SOURCE_DIR}/assets
    ${PROJECT_BINARY_DIR}/$<CONFIGURATION>/assets
    COMMENT "Copying assets into binary directory")

add_dependencies(${PROJECT_NAME} copy_shaders copy_assets)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_compile_options(${PROJECT_NAME} PRIVATE -ggdb -Wall -Wextra -Wconversion -Wsign-conversion -Wfatal-errors
    -Wunused-variable -Wsuggest-attribute=const)

target_link_libraries(${PROJECT_NAME} PRIVATE LibraC)
