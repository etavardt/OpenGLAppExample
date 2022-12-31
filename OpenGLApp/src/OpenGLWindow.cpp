#include "OpenGLWindow.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "OpenGLDebug.hpp"
#include "KewlF/Logger.hpp"

//OpenGLWindow::OpenGLWindow() : width(2048), height(1536) {
OpenGLWindow::OpenGLWindow() : width(800) , height(800) {


    /* Initialize the library */
    if (!glfwInit())
        throw "Failed call to glfwInit";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "OpenGL", NULL, NULL);
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

    // Scale and Translate positions
    for (int i = 0; i < vertexBuf.size(); i += 4) {
        // Scale positions
        vertexBuf[i] *= 500;
        vertexBuf[i + 1] *= 500;
        // Translate positions
        vertexBuf[i] += width / 2;
        vertexBuf[i + 1] += height / 2;

    }

    vb = new VertexBuffer(vertexBuf.data(), sizeof(vertexBuf));
    ib = new IndexBuffer(indices, 6);
    va = new VertexArray();
    shader = new Shader("res/shaders/basic.shader");
    //texture = new Texture("res/textures/_MG_1005.bmp");
    //texture = new Texture("res/textures/newday2.bmp");
    texture = new Texture("res/textures/Superfluous-Organ-1.jpg");
    
    //renderer = new
  
    //std::cout << "OpenGLWindow Constructed" << std::endl;
}

OpenGLWindow::~OpenGLWindow() {
    delete texture;
    delete shader;
    delete va;
    delete ib;
    delete vb;

    glfwTerminate();

    //std::cout << "OpenGLWindow Destructed" << std::endl;
}

void OpenGLWindow::init() {
    LOG(INFO) << glGetString(GL_VERSION) << std::endl;

    // Set Projection Matrix
    glm::mat4 proj = glm::ortho(0.0f, width*1.0f, 0.0f, height*1.0f, -1.0f, 1.0f); // Orthographic Projection
    //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); // Orthographic Projection
    //glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f); // Orthographic Projection
    //glm::vec4 vp(100.0f, 100.0f, 0.0f, 1.0f);
    //glm::vec4 result = proj * vp;

    // Setup Blending
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Setup a Vertex Array
    va->bind();
    layout.push<float>(2); // vertices
    layout.push<float>(2); // texture mapping
    va->addBuffer(*vb, layout);

    // Setup a Shader
    shader->bind();
    shader->setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    shader->setUniformMat4f("u_MVP", proj);

    // Setup a Texture
    texture->bind();
    shader->setUniform1i("u_Texture", 0);

    // Unbind once setup
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
        renderer.clear();

        /* // Animate color change
        // Bind Shader to make changes
        shader->bind();
        shader->setUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);
        */

        renderer.draw(*va, *ib, *shader);

        /* // Animate color
        if (r > 1.0f)
            increment = -0.05f;
        else if (r < 0.0f)
            increment = 0.05f;

        r += increment;
        */

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}