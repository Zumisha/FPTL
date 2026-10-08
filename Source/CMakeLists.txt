cmake_minimum_required(VERSION 3.5)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        "*.cpp"
        "*.c"
        "*.cc"
        "*.hpp"
        "*.h"
        "*.hh"
)

add_library(Source ${SOURCES})