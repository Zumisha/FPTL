<<<<<<< Updated upstream:CMakeLists.txt
add_subdirectory(Runtime)
=======
cmake_minimum_required(VERSION 3.0)

# Vars
set(PROJECT_NAME FPTL)
get_filename_component(PROJECT_DIR "${CMAKE_CURRENT_SOURCE_DIR}" ABSOLUTE)
set(OUTPUT_DEBUG "build/bin")
set(OUTPUT_RELEASE "build/bin")
#set(VERBOSE 1)

# Project
project(${PROJECT_NAME} CXX)
#add_subdirectory(Parser)

if(VERBOSE)
  message("${PROJECT_NAME}: MAIN PROJECT: ${CMAKE_PROJECT_NAME}")
  message("${PROJECT_NAME}: CURR PROJECT: ${CMAKE_CURRENT_SOURCE_DIR}")
  message("${PROJECT_NAME}: CURR BIN DIR: ${CMAKE_CURRENT_BINARY_DIR}")
endif()

# Include directories 
include_directories($ENV{BOOST_ROOT})
include_directories(../Thirdparty/lib/)
include_directories(../Thirdparty/jemalloc-5.0.1/lib/)
include_directories(../Thirdparty/jemalloc-5.0.1/include/)
include_directories(./)
include_directories(./Parser/Generated/Flex/)

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

# Source Files
set(SRC_FILES
  Main.cpp
  
  DataTypes/TypeInfo.cpp
  
  DataTypes/Values/ADTValue.cpp
  
  Evaluator/Context.cpp
  Evaluator/EvaluatorUnit.cpp
  Evaluator/Run.cpp
  
  FScheme/ConstructorGenerator.cpp 
  FScheme/FScheme.cpp
  FScheme/FSchemeGenerator.cpp
  FScheme/NodeDeleter.cpp
  
  InternalForm/Generator.cpp
  InternalForm/InternalForm.cpp
  
  Libraries/FunctionLibrary.cpp
  Libraries/StandardLibrary.cpp
  
  Parser/Nodes.cpp
  Parser/NodeVisitor.cpp
  Parser/Semantic.cpp
  Parser/Support.cpp
  Parser/Tokenizer.cpp
  
  Parser/Generated/Parser.tab.cc
  Parser/Generated/Flex/FlexScanner.cpp
)
source_group("Sources" FILES ${SRC_FILES})

# Header Files
set(HEADERS_FILES
Macros.h

DataTypes/TypeInfo.h

DataTypes/Ops/ADTOps.h
DataTypes/Ops/ArrayOps.h
DataTypes/Ops/BaseOps.h
DataTypes/Ops/BooleanOps.h
DataTypes/Ops/DoubleOps.h
DataTypes/Ops/IntegerOps.h
DataTypes/Ops/Ops.h

DataTypes/Ops/StringOps.h
DataTypes/Values/ADTValue.h
DataTypes/Values/ArrayValue.h
DataTypes/Values/StringValue.h
DataTypes/Values/Value.h

Evaluator/Context.h
Evaluator/ControlValue.h
Evaluator/EvaluatorUnit.h
Evaluator/LockFreeWorkStealingQueue.h
Evaluator/Run.h

FScheme/ConstructorGenerator.h
FScheme/FScheme.h
FScheme/FSchemeGenerator.h
FScheme/FSchemeVisitor.h
FScheme/NodeDeleter.h

InternalForm/Generator.h
InternalForm/InternalForm.h

Libraries/FunctionLibrary.h
Libraries/StandardLibrary.h

Parser/AST.h
Parser/FlexTokenizer.h
Parser/Ident.h
Parser/Nodes.h
Parser/NodeVisitor.h
Parser/SemanticCheck.h
Parser/Support.h

Parser/Generated/Parser.tab.hh
Parser/Generated/stack.hh
Parser/Generated/Flex/FlexLexer.h

Utils/FormatedOutput.h
)
source_group("Headers" FILES ${HEADERS_FILES})

# Add executable to build.
add_executable(${PROJECT_NAME} 
   ${SRC_FILES} ${HEADERS_FILES}
)

#add_subdirectory(Runtime)

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
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES} )
#target_link_libraries(${PROJECT_NAME} libjemalloc.so )
>>>>>>> Stashed changes:Source/CMakeLists.txt
