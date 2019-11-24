# File generated at : 01:55:11, Fri 22 Nov 
# Converted Project : Thirdparty/jemalloc-5.0.1/msvc/projects/vc2015/test_threads/test_threads.vcxproj
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

##################### Variables ############################
# Change if you want modify path or other values           #
############################################################

# Project
get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(DEPENDENCIES_DIR ${PROJECT_DIR}/dependencies)
set(PROJECT_NAME test_threads)

# Dependencies
set(JEMALLOC_DIR ../jemalloc)

# Outputs
set(OUTPUT_DEBUG ./)
set(OUTPUT_RELEASE ./)

################# CMake Project ############################
# The main options of project                              #
############################################################

project(${PROJECT_NAME} CXX)

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
include_directories(../../../../test/include)
include_directories(../../../../include)
include_directories(../../../../include/msvc_compat)
include_directories(%(AdditionalIncludeDirectories))

################## Dependencies ############################
# Add Dependencies to project                              #
############################################################

# Dependencies: disable BUILD_DEPENDS to link with libraries already built
option(BUILD_DEPENDS "Build other CMake project." ON)

if(BUILD_DEPENDS)
  if(NOT TARGET jemalloc)
    add_subdirectory("${JEMALLOC_DIR}" ${CMAKE_BINARY_DIR}/jemalloc)
  endif()
else()
   link_directories(${DEPENDENCIES_DIR}/jemalloc)
endif()

############### Files & Targets ############################
# Files of project and target to build                     #
############################################################

# Source Files
set(SRC_FILES
    ./test_threads.cpp
    ./test_threads_main.cpp
)
source_group("Sources" FILES ${SRC_FILES})

# Header Files
set(HEADERS_FILES
    test_threads.h
)
source_group("Headers" FILES ${HEADERS_FILES})

# Add executable to build.
add_executable(${PROJECT_NAME} 
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
   -DNDEBUG 
   -D_CONSOLE 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /GL /Oi /Gy /Zi /EHsc)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -D_DEBUG 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /MD /Od /Zi /EHsc)
    endif()
endif()

########### Link & Dependencies ############################
# Add project dependencies and Link to project             #
############################################################

# Project dependencies
add_dependencies(${PROJECT_NAME} jemalloc)

# Link with other dependencies.
target_link_libraries(${PROJECT_NAME} jemalloc )
if(MSVC)
   target_link_libraries(${PROJECT_NAME} jemallocd.lib kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib )
endif(MSVC)
