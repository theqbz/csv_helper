cmake_minimum_required ( VERSION 3.12 )

project ( csv_helper VERSION 1.0 DESCRIPTION "CSV file conent analyzer" )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_VERBOSE_MAKEFILE ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake )

conan_basic_setup( TARGETS )

add_subdirectory( src )

