# CMakeList.txt : CMake project for 3rdParty projects
# project specific logic here.
#

# Include sub-projects.
add_subdirectory ("glfw")
add_subdirectory ("KewlFLib/KewlF")

# TODO: posibly move this to KewlF to keep the include and lib in its own project and add those locations to 
#       includw and lib variable in projects that want to use KewlF
#file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/KewlFlib/KewlF/src/
#     DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/include/KewlF
#     FILES_MATCHING PATTERN src/*.hpp
#)

# can a post build call for KewlF be done here?
# even though the lib is found automaticaly do it as well as the header files?
