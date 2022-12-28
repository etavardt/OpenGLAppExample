# CMakeList.txt : CMake project for OpenGLApp, include source and define
# project specific logic here.
#

include_directories(
    src/
    ../3rdParty/include/
)

#link_directories([AFTER|BEFORE] directory1 [directory2 ...])
link_directories(
    ../3rdParty/lib
)

# Add source to this project's executable.
file(GLOB SOURCE_FILES LIST_DIRECTORIES false
    src/*.cpp
    src/*.h
    src/*.hpp
)

# Add source to this project's executable.
add_executable (OpenGLApp ${SOURCE_FILES})
target_link_libraries(OpenGLApp KewlF glfw3 glew32s ${OPENGL_LIBRARY})
target_compile_definitions(OpenGLApp PUBLIC GLEW_STATIC)
# TODO: Wrap in Debug test
target_compile_definitions(OpenGLApp PUBLIC DEBUG_GL)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGLApp PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(
    TARGET OpenGLApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/OpenGLApp/res ${CMAKE_BINARY_DIR}/OpenGLApp/res
    COMMENT "Copying recources" VERBATIM
)
# TODO: Add tests and install targets if needed.
