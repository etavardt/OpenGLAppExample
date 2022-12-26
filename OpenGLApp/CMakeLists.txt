# CMakeList.txt : CMake project for OpenGLApp, include source and define
# project specific logic here.
#

include_directories(
    src/
    ../3rdParty/include/
    ../3rdParty/easyloggingpp/src
)

#link_directories([AFTER|BEFORE] directory1 [directory2 ...])
link_directories(
    ../3rdParty/lib
)

# Add source to this project's executable.
file(GLOB SOURCE_FILES LIST_DIRECTORIES false
    ../3rdParty/easyloggingpp/src/*.cc
    src/*.cpp
    src/*.h
    src/*.hpp
)

# Add source to this project's executable.
add_executable (OpenGLApp ${SOURCE_FILES})
target_link_libraries(OpenGLApp KewlF glfw3 glew32s)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGLApp PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
