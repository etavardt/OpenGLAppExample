#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <KewlF/Window.hpp>
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"

class OpenGLWindow : Window {
private:
	GLFWwindow* window;

//	GLsizei bufNamesSize = 1;
//	GLuint* bufNames = (GLuint*)alloca(bufNamesSize*sizeof(GLuint)); // bufNames[];
	//unsigned int shader; //GLuint
	//int cLoc; //GLint
    
    //unsigned int ibo; //GLuint
    //unsigned int vao; //GLuint
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
    VertexBufferLayout layout;
    VertexArray* va;
    VertexBuffer* vb;
    IndexBuffer*  ib;
    Shader* shader;
    Renderer renderer;

public:
	OpenGLWindow();
	~OpenGLWindow();

	void init() override;
	//void show() override;

	void pullEvents();
};