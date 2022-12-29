#pragma once

#include <GLFW/glfw3.h>
#include <KewlF/Window.hpp>

class OpenGLWindow : Window {
private:
	GLFWwindow* window;

	GLsizei bufNamesSize = 1;
	GLuint* bufNames = (GLuint*)alloca(bufNamesSize*sizeof(GLuint)); // bufNames[];
	GLuint shader;
	GLint cLoc;
    
    GLuint ibo;
    GLuint vao;
    //Vertex Buffer
    float vertexBuf[8] = {
        -0.5f, -0.5f, //0
         0.5f, -0.5f, //1
         0.5f,  0.5f, //2
        -0.5f,  0.5f  //3
    };

    //Indices buffer
    unsigned int indices[6] = {
        0,1,2,
        2,3,0
    };

public:
	OpenGLWindow();
	~OpenGLWindow();

	void init() override;
	//void show() override;

	void pullEvents();
};