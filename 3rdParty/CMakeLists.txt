# CMakeList.txt : CMake project for 3rdParty projects
# project specific logic here.
#

include(FetchContent)

#find_package(backtrace REQUIRED)

#FetchContent_Declare(
#    libbacktrace
#    GIT_REPOSITORY https://github.com/etavardt/libbacktrace.git
#    #GIT_TAG        ???
#)

## Check if population has already been performed
#FetchContent_GetProperties(libbacktrace)
#string(TOLOWER "libbacktrace" lcName)
#if(NOT ${lcName}_POPULATED)

# Fetch the content using previously declared details
# FetchContent_Populate(libbacktrace)

#  # Set custom variables, policies, etc.
#  # ...

#  # Bring the populated content into the build
#  add_subdirectory(${${lcName}_SOURCE_DIR} ${${lcName}_BINARY_DIR})
#endif()

#FetchContent_Declare(
#    KewlFLib
#    GIT_REPOSITORY https://github.com/etavardt/KewlFLib.git
#)

#FetchContent_Declare(
#    glfw
#    GIT_REPOSITORY https://github.com/glfw/glfw.git
#)

#FetchContent_Declare(
#    glew
#    GIT_REPOSITORY https://github.com/nigels-com/glew.git
#)

#FetchContent_Declare(
#    glm
#    GIT_REPOSITORY https://github.com/g-truc/glm.git
#)

#FetchContent_MakeAvailable(KewlFLib glfw glew glm)
