cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXENSIONS ON)

set(CMAKE_CXX_COMPILER "clang++")

project(myDataStructures LANGUAGES CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    message("the current mode is Debug.")
endif()

aux_source_directory(./ DIR_SRCS)

include_directories(${PROJECT_SOURCE_DIR}/5_chapter)
include_directories(${PROJECT_SOURCE_DIR}/6_chapter)
include_directories(${PROJECT_SOURCE_DIR}/10_chapter_hash)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)

add_executable(myDataStructures ${DIR_SRCS})

message("comple and link is complete.")
