# CMakeList.txt : CMake project for OpenGLApp, include source and define
# project specific logic here.
#

include_directories(
    src/
    tests/
    ../3rdParty/include/
    ../3rdParty/glfw/include/
    ../3rdParty/imgui/src/
    ../3rdParty/KewlFlib/KewlF/src
    ../3rdParty/glad/include/
)

#link_directories([AFTER|BEFORE] directory1 [directory2 ...])
link_directories(
    ../3rdParty/lib
)

# Add source to this project's executable.
file(GLOB SOURCE_FILES LIST_DIRECTORIES false
    src/*.cpp
    tests/*.cpp
    ../3rdParty/glad/src/*.c
    ../3rdParty/imgui/src/*.cpp
)

# Add source to this project's executable.
add_executable (OpenGLApp ${SOURCE_FILES})
target_link_libraries(OpenGLApp KewlF glfw ${OPENGL_LIBRARY})
# TODO: Wrap in Debug test
target_compile_definitions(OpenGLApp PUBLIC DEBUG_GL KEWLF_DEBUG)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OpenGLApp PROPERTY CXX_STANDARD 20)
endif()

add_custom_command(
    TARGET OpenGLApp PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/OpenGLApp/res ${CMAKE_BINARY_DIR}/OpenGLApp/res
    COMMENT "Copying recources" VERBATIM
)

add_custom_command(
    TARGET OpenGLApp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/OpenGLApp/res ${CMAKE_BINARY_DIR}/OpenGLApp/res
    COMMENT "Copying recources" VERBATIM
)
# TODO: Add tests and install targets if needed.
