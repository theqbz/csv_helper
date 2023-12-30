cmake_minimum_required ( VERSION 3.12 )

project ( csv_helper VERSION 1.0 DESCRIPTION "CSV file conent analyzer" )

####################################################
# Set output directories for multi-config generators
####################################################

foreach( CONFIG ${CMAKE_CONFIGURATION_TYPES} )
    string(TOUPPER ${CONFIG} CONFIG)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/lib)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIG} ${CMAKE_BINARY_DIR}/bin)
endforeach()

#####################################################
# Set output directories for single-config generators
#####################################################

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

cmake_policy( SET CMP0091 NEW )

set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_VERBOSE_MAKEFILE ON )
set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

list( APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake )

include( ${CMAKE_SOURCE_DIR}/conan/conan_toolchain.cmake )
find_package( GTEST REQUIRED )
find_package( FTXUI REQUIRED )
# conan_basic_setup( TARGETS )

add_subdirectory( src )

