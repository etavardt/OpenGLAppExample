#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <KewlF/Window.hpp>
#include <array>
#include "IndexBuffer.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "VertexBufferLayout.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Texture.hpp"

class OpenGLWindow : Window {
private:
	GLFWwindow* window;

    unsigned int width;
    unsigned int height;
//	GLsizei bufNamesSize = 1;
//	GLuint* bufNames = (GLuint*)alloca(bufNamesSize*sizeof(GLuint)); // bufNames[];
	//unsigned int shader; //GLuint
	//int cLoc; //GLint
    
    //unsigned int ibo; //GLuint
    //unsigned int vao; //GLuint
    //Vertex Buffer
    //float* vertexBuf;
    //float vertexBuf[16] = {
    std::array<float, 16> vertexBuf = {
        -0.5f, -0.5f, 0.0f, 0.0f, //0
         0.5f, -0.5f, 1.0f, 0.0f, //1
         0.5f,  0.5f, 1.0f, 1.0f, //2
        -0.5f,  0.5f, 0.0f, 1.0f  //3
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
    Texture* texture;

    glm::mat4 proj;
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 mvp;

    float hw = 0;
    float hh = 0;
public:
	OpenGLWindow();
	~OpenGLWindow();

	void init() override;
	//void show() override;

	void pullEvents();
};