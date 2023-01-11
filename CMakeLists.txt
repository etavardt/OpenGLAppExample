# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
#
cmake_minimum_required (VERSION 3.8)

project ("OpenGLAppExample")

include(CMakePrintHelpers) #Example usage: cmake_print_variables(SOURCE_FILES)
cmake_print_variables(CMAKE_INSTALL_LIBDIR)
cmake_print_variables(CMAKE_BUILD_DIR)

# OpenGL
find_package(OpenGL REQUIRED)

# Include sub-projects.
add_subdirectory ("3rdParty")
add_subdirectory ("OpenGLApp")
