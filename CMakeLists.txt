# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenGLAppExample")

#include_directories(
#    ../3rdParty/easyloggingpp/src/
#    ../3rdParty/include/
#)

#link_directories([AFTER|BEFORE] directory1 [directory2 ...])
link_directories(
    ../3rdParty/lib
)

# Include sub-projects.
add_subdirectory ("3rdParty")
add_subdirectory ("OpenGLApp")
