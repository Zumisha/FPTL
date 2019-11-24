# File generated at : 01:53:48, Fri 22 Nov 
# Converted Project : Thirdparty/jemalloc-5.0.1/msvc/projects/vc2015/jemalloc/jemalloc.vcxproj
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

##################### Variables ############################
# Change if you want modify path or other values           #
############################################################

# Project
get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(DEPENDENCIES_DIR ${PROJECT_DIR}/dependencies)
set(PROJECT_NAME jemalloc)


# Outputs
set(OUTPUT_DEBUG ./)
set(OUTPUT_RELEASE ./)

################# CMake Project ############################
# The main options of project                              #
############################################################

project(${PROJECT_NAME} C)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif(NOT CMAKE_BUILD_TYPE)

############## Artefacts Output ############################
# Defines outputs , depending BUILD TYPE                   #
############################################################

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
endif()

# Messages
message("${PROJECT_NAME}: MAIN PROJECT: ${CMAKE_PROJECT_NAME}")
message("${PROJECT_NAME}: CURR PROJECT: ${CMAKE_CURRENT_SOURCE_DIR}")
message("${PROJECT_NAME}: CURR BIN DIR: ${CMAKE_CURRENT_BINARY_DIR}")

###################### Includes ############################
# Include files and directories                            #
############################################################

# Include directories 
include_directories(../../../../include)
include_directories(../../../../include/msvc_compat)
include_directories(%(AdditionalIncludeDirectories))

############### Files & Targets ############################
# Files of project and target to build                     #
############################################################

# Source Files
set(SRC_FILES
    ../../../../src/arena.c
    ../../../../src/background_thread.c
    ../../../../src/base.c
    ../../../../src/bitmap.c
    ../../../../src/ckh.c
    ../../../../src/ctl.c
    ../../../../src/extent.c
    ../../../../src/extent_dss.c
    ../../../../src/extent_mmap.c
    ../../../../src/hash.c
    ../../../../src/hooks.c
    ../../../../src/jemalloc.c
    ../../../../src/large.c
    ../../../../src/malloc_io.c
    ../../../../src/mutex.c
    ../../../../src/mutex_pool.c
    ../../../../src/nstime.c
    ../../../../src/pages.c
    ../../../../src/prng.c
    ../../../../src/prof.c
    ../../../../src/rtree.c
    ../../../../src/spin.c
    ../../../../src/stats.c
    ../../../../src/sz.c
    ../../../../src/tcache.c
    ../../../../src/ticker.c
    ../../../../src/tsd.c
    ../../../../src/witness.c
)
source_group("Sources" FILES ${SRC_FILES})

# Header Files
set(HEADERS_FILES
)
source_group("Headers" FILES ${HEADERS_FILES})

# Add library to build.
add_library(${PROJECT_NAME} SHARED
   ${SRC_FILES} ${HEADERS_FILES}
)

######################### Flags ############################
# Defines Flags for Windows and Linux                      #
############################################################

if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
endif(NOT MSVC)

# Preprocessor definitions
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -D_REENTRANT 
   -D_WINDLL 
   -DDLLEXPORT 
   -DNDEBUG 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /GL /Oi /Gy /Zi /EHsc)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -DJEMALLOC_NO_PRIVATE_NAMESPACE 
   -D_REENTRANT 
   -D_WINDLL 
   -DDLLEXPORT 
   -DJEMALLOC_DEBUG 
   -D_DEBUG 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /MD /Od /Zi /EHsc)
    endif()
endif()

########### Link & Dependencies ############################
# Add project dependencies and Link to project             #
############################################################

