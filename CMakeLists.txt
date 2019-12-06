cmake_minimum_required(VERSION 3.0)

# Vars
set(PROJECT_NAME FPTL)
get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(OUTPUT_DEBUG "bin")
set(OUTPUT_RELEASE "bin")

# Project
project(${PROJECT_NAME} CXX)

#message("${PROJECT_NAME}: MAIN PROJECT: ${CMAKE_PROJECT_NAME}")
#message("${PROJECT_NAME}: CURR PROJECT: ${CMAKE_CURRENT_SOURCE_DIR}")
#message("${PROJECT_NAME}: CURR BIN DIR: ${CMAKE_CURRENT_BINARY_DIR}")

######################### Flags ############################
# Defines Flags for Windows and Linux                      #
############################################################

if(NOT MSVC)
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
   if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
       set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
   endif()
endif(NOT MSVC)

# Include directories 
include_directories($ENV{BOOST_ROOT})
include_directories(${Boost_INCLUDE_DIR})
include_directories(./Thirdparty/lib/)
include_directories(./Thirdparty/jemalloc-5.0.1/lib/)
include_directories(./Thirdparty/jemalloc-5.0.1/include/)
include_directories(./Source/)
include_directories(./Source/Parser/Generated/Flex/)

add_subdirectory(Source)
add_executable(${PROJECT_NAME} Source/Main.cpp)

# Define Release by default.
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
  message(STATUS "Build type not specified: Use Release by default.")
endif()
# Defines outputs , depending BUILD TYPE
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_DEBUG}")
else()
  set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
  set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${PROJECT_DIR}/${OUTPUT_RELEASE}")
endif()

###################### Warnings ############################
# uncomment to add extra gcc warnings                      #
############################################################
#add_compile_options(-Wall)
#add_compile_options(-Wextra)

###################### Address sanitizer ###################
# uncomment to add address sanitizer                       #
############################################################
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-omit-frame-pointer -fsanitize=address")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")

###################### Undefined behaviour sanitizer #######
# uncomment to add undefined behaviour sanitizer           #
############################################################
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fuse-ld=gold -fno-omit-frame-pointer -fsanitize=undefined")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fuse-ld=gold -fno-omit-frame-pointer -fsanitize=undefined")

###################### Thread sanitizer ###################
# uncomment to add thread sanitizer                       #
############################################################
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-omit-frame-pointer -fsanitize=thread")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=thread")

###################### Memory sanitizer ###################
# uncomment to add memory sanitizer                       #
############################################################
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -fno-omit-frame-pointer -fsanitize=memory")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=memory")

# Preprocessor definitions
if(CMAKE_BUILD_TYPE STREQUAL "Release")
    message("Release")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -DNDEBUG 
   -D_CONSOLE 
   -DGC_BUILD 
   -DGC_WIN32_THREADS 
   -D 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /GL /Oi /Gy /Zi /EHsc)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message("Debug")
    target_compile_definitions(${PROJECT_NAME} PRIVATE 
   -D_DEBUG 
   -D_CONSOLE 
   -DGC_BUILD 
   -DGC_WIN32_THREADS 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /MDd /Od /Zi /EHsc)
    endif()
endif()

########### Link & Dependencies ############################
# Add project dependencies and Link to project             #
############################################################

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)

# export BOOST_ROOT=/mnt/c/Libraries/boost_1_69_0/
FIND_PACKAGE(Boost 1.58 COMPONENTS program_options timer thread chrono date_time atomic REQUIRED)
#message(STATUS "Found boost incl: ${Boost_INCLUDE_DIR}")
#message(STATUS "Found boost lib: ${Boost_LIBRARY_DIRS}")
#message(STATUS "Boost libs to link: ${Boost_LIBRARIES}")

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} )
target_link_libraries(${PROJECT_NAME} libjemalloc.so )
target_link_libraries(${PROJECT_NAME} Source)

# cmake ../Source -DCMAKE_BUILD_TYPE=Release
