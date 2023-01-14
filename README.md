# OpenGLAppExample
---
An OpenGL Example Application for C++ (A work in progress)

## OpenGLApp
The example app to demonstrate how to use modern opengl.

## External Libraries used
- GLFW
    ~ OpenGL Windowing
- GLAD
    ~ OpenGL Interface
- GLM
    ~ OpenGL Math Library
- stb
    ~ The stb image portion for loading image files.
- Dear imGui
    ~ A GUI interface for menus, tools, controls, etc..
- KewlF (The Kewl Application Framework) (Personal Project-a work in progress)
    ~ A platform independent C++ Object Oriented Application Framework.
    ~ When cloning:
        ~ `git clone --recursive https://github.com/etavardt/OpenGLAppExample.git`

## Log
    ??/??/???? Started this from following an OpenGL tutorial on 'TheCherno's
               youTube channel.  But there are elements of my own and at least 
               one idea from a youTube user's comment on a "TheCherno"s video.
    01/12/2023 Abandoned GLEW for GLAD do to ease of use, no libs and just headers
               and a c file to build. Just link it yourself, in your project.
               Therefore there are no binary compatibility issues.  The only issue
               with GLAD is the website configureing of those files.  It is a boon 
               and a bane,having to rely on a website that may or maynot be there in
               the future. Whether it is due to connectivity or being nolonger supported.
