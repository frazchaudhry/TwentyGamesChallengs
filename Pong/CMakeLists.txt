cmake_minimum_required(VERSION 3.15...4.11)
project(Pong C CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

file(GLOB SOURCES "src/*.cpp")

add_executable(${PROJECT_NAME} ${SOURCES})

list(APPEND LIBRAC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/src)
list(APPEND LIBRAC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/src/linux)
list(APPEND LIBRAC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/src/windows)
list(APPEND LIBRAC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/external/stb)
list(APPEND LIBRAC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/external/cglm)
list(APPEND LIBRAC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/external/debug_break)
list(APPEND LIBRAC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/external/GLAD/include)
list(APPEND LIBRAC_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/external/SDL/include)
add_library(LibraC STATIC IMPORTED)
set_target_properties(LibraC PROPERTIES
    IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/build/libLibraC.a
    INTERFACE_INCLUDE_DIRECTORIES "${LIBRAC_INCLUDES}")

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

target_link_libraries(${PROJECT_NAME} PRIVATE LibraC ${CMAKE_CURRENT_SOURCE_DIR}/../libs/LibraC/build/external/GLAD/libglad.a -lSDL3 -lm)
