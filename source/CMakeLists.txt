cmake_minimum_required(VERSION 3.15)

# Project name and programming language
project( PIPENETWORK CXX )

# Gather file names and store them in CMake variables
file( GLOB LIBRARY_SOURCE_FILES library/src/*.cpp )
file( GLOB TEST_SOURCE_FILES library/test/*.cpp )
file( GLOB HEADER_FILES library/inc/*.h* )

# Enables exporting all symbols to the dll on windows
set( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )


# Add compilation target for our library. Adding header files here will make 
# them show up in Visual Studio. We still need to set include folders later.
add_library( pipenetwork SHARED ${LIBRARY_SOURCE_FILES} ${HEADER_FILES} )

# Add compilation target for our executables
add_executable( main drivers/main.cpp )
add_executable( testrunner ${TEST_SOURCE_FILES} )


# Add include dependencies
target_include_directories( pipenetwork PUBLIC library/inc )
target_include_directories( main PUBLIC library/inc )
target_include_directories( testrunner PUBLIC 
                            library/inc external/catch2 )

# Add link dependencies
target_link_libraries( testrunner PUBLIC pipenetwork )
target_link_libraries( main PUBLIC pipenetwork )