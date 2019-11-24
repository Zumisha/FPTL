# File generated at : 02:04:17, Fri 22 Nov 
# Converted Project : Runtime/Runtime.vcxproj
cmake_minimum_required(VERSION 3.0.0 FATAL_ERROR)

##################### Variables ############################
# Change if you want modify path or other values           #
############################################################

# Project
get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(DEPENDENCIES_DIR ${PROJECT_DIR}/dependencies)
set(PROJECT_NAME Runtime)


# Outputs
set(OUTPUT_DEBUG ${PROJECT_DIR}/bin)
set(OUTPUT_RELEASE ${PROJECT_DIR}/bin)

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
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -L../../Thirdparty/jemalloc-5.0.1/lib -fuse-ld=gold -fno-omit-frame-pointer -fsanitize=undefined")
#set (CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -L../../Thirdparty/jemalloc-5.0.1/lib -fuse-ld=gold -fno-omit-frame-pointer -fsanitize=undefined")

###################### Includes ############################
# Include files and directories                            #
############################################################

# Include directories 
include_directories(../)
include_directories(../Parser/Generated/Flex)
include_directories(../Parser/Generated)
include_directories($ENV{BOOST_PATH}/)
include_directories(../External/gc/gc-7.2/include)
include_directories(../External/AsmJit/AsmJit)
include_directories($ENV{PYTHON_PATH}/include)
include_directories(../Thirdparty/jemalloc-5.0.1/include)

############### Files & Targets ############################
# Files of project and target to build                     #
############################################################

# Source Files
set(SRC_FILES
    ./ADT.cpp
    ./FScheme.cpp
    ./NodeDeleter.cpp
    ./FSchemeGenerator.cpp
    ./Run.cpp
    ./CollectedHeap.cpp
    ./ConstructorGenerator.cpp 
    ./FunctionLibrary.cpp
    ./Context.cpp
    ./GarbageCollector.cpp
    ./StandardLibrary.cpp
    ./EvaluatorUnit.cpp
    ./Main.cpp
    ./DataTypes/Bool.cpp
    ./DataTypes/String.cpp
    ./DataTypes/Array.cpp
    ./DataTypes/Double.cpp
    ./DataTypes/Undefined.cpp
    ./DataTypes/Data.cpp
    ./DataTypes/Int.cpp
    ./DataTypes/Types.cpp
    ./IntForm/Generator.cpp
    ./IntForm/InternalForm.cpp
    ../Parser/NodeVisitor.cpp
    ../Parser/Support.cpp
    ../Parser/Tokenizer.cpp
    ../Parser/Nodes.cpp
    ../Parser/Semantic.cpp
    ../Parser/TypeCheck.cpp
    ../Parser/Generated/Parser.tab.cc
    ../Parser/Generated/Flex/FlexScanner.cpp
)
source_group("Sources" FILES ${SRC_FILES})

# Header Files
set(HEADERS_FILES
    BlockingQueue.h
    NodeDeleter.h
    FSchemeGenerator.h
    FScheme.h
    Run.h
    CollectedHeap.h
    FSchemeVisitor.h
    ConstructorGenerator.h
    FunctionLibrary.h
    Context.h
    GarbageCollector.h
    Core.h
    GcAwarePtr.h
    StandardLibrary.h
    WorkStealingQueue.h
    LockFreeWorkStealingQueue.h
    EvaluatorUnit.h
    DataTypes/ADT.h
    DataTypes/Data.h
    DataTypes/Types.h
    DataTypes/String.h
    DataTypes/Array.h
    IntForm/ControlValue.h
    IntForm/Generator.h
    IntForm/InternalForm.h
    ../Parser/AST.h
    ../Parser/TypeCheck.h
    ../Parser/FlexTokenizer.h
    ../Parser/NodeVisitor.h
    ../Parser/Support.h
    ../Parser/Types.h
    ../Parser/Ident.h
    ../Parser/SemanticCheck.h
    ../Parser/Tokenizer.h
    ../Parser/Nodes.h
    ../Parser/Generated/Parser.tab.hh
    ../Parser/Generated/stack.hh
    ../Parser/Generated/Flex/FlexLexer.h
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
   -DGC_BUILD 
   -DGC_WIN32_THREADS 
   -D 
    )
    if(MSVC)
        target_compile_options(${PROJECT_NAME} PRIVATE  /W3 /GL /Oi /Gy /Zi /EHsc)
    endif()
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
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
FIND_PACKAGE( Boost 1.58 COMPONENTS program_options timer thread REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} )


   target_link_libraries(${PROJECT_NAME} libjemalloc.so )
if(MSVC)
   target_link_libraries(${PROJECT_NAME} libtcmalloc_minimal-debug.lib )
endif(MSVC)
