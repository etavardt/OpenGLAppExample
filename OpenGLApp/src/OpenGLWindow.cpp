#include "OpenGLWindow.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include "OpenGLDebug.hpp"
#include "Renderer.hpp"

OpenGLWindow::OpenGLWindow() {
    /* Initialize the library */
    if (!glfwInit())
        throw "Failed call to glfwInit";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1820, 1440, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Failed call to glfwCreateWindow";
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cerr << "glewInit Failed" << std::endl;
    }
    glDebug::initialize();

    vb = new VertexBuffer(vertexBuf, sizeof(vertexBuf));
    ib = new IndexBuffer(indices, 6);
    va = new VertexArray();
    shader = new Shader("res/shaders/basic.shader");
    //std::cout << "OpenGLWindow Constructed" << std::endl;
}

OpenGLWindow::~OpenGLWindow() {
    delete shader;
    delete va;
    delete ib;
    delete vb;

    glfwTerminate();

    //std::cout << "OpenGLWindow Destructed" << std::endl;
}

void OpenGLWindow::init() {
    std::cout << glGetString(GL_VERSION) << std::endl;

    //GLCall(glGenVertexArrays(1, &vao));
    //GLCall(glBindVertexArray(vao));
    va->bind();
    layout.push<float>(2);
    va->addBuffer(*vb, layout);

    shader->bind();
    shader->setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    //unbind for vertex array example from The Cherno's YT chnl
    va->unbind();
    vb->unbind();
    ib->unbind();
    shader->unbind();
}

void OpenGLWindow::pullEvents() {
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        shader->bind();
        shader->setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        va->bind();
        ib->bind();

        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}