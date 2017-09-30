project(jack_syntax_analyser)

# Minimum version of CMake
cmake_minimum_required(VERSION 3.0)

# Boost Libraries - Used for filesystem only
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED OFF)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost COMPONENTS filesystem)

# Compilation flags
set(CMAKE_CXX_FLAGS "--std=c++14 -g -Wall -pedantic -Wextra -Werror")
set(BUILD_SHARED_LIBS true)

# CMake/Make output options
set(CMAKE_COLOR_MAKEFILE true)
set(CMAKE_VERBOSE_MAKEFILE false)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# File generation options
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY lib)
set(${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY bin)
set(${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY lib)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${${PROJECT_NAME}_LIBRARY_OUTPUT_DIRECTORY})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${${PROJECT_NAME}_ARCHIVE_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/${${PROJECT_NAME}_RUNTIME_OUTPUT_DIRECTORY})

# Tree parsing
add_subdirectory(tokeniser)
add_subdirectory(symbol_table)
add_subdirectory(grammar_engine)
add_subdirectory(main_app)
