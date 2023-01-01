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
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

//OpenGLWindow::OpenGLWindow() : width(800) , height(800) {
OpenGLWindow::OpenGLWindow() : width(2048), height(1536) {

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

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Scale and Translate positions
    for (int i = 0; i < vertexBuf.size(); i += 4) {
        // Scale positions
        vertexBuf[i] *= 500;
        vertexBuf[i + 1] *= 500;
        // Translate positions
        //vertexBuf[i] += width / 2;
        //vertexBuf[i + 1] += height / 2;

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

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    //std::cout << "OpenGLWindow Destructed" << std::endl;
}

void OpenGLWindow::init() {
    LOG(INFO) << glGetString(GL_VERSION) << std::endl;

    // Set Projection Matrix
    //glm::mat4 proj = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f); // Orthographic Projection
    //glm::mat4 proj = glm::ortho(-4.0f, 4.0f, -3.0f, 3.0f, -1.0f, 1.0f); // Orthographic Projection
    //glm::vec4 vp(100.0f, 100.0f, 0.0f, 1.0f);
    //glm::vec4 result = proj * vp;
    //glm::mat4 view = glm::translate(glm::vec3(-100.0f, 0.0f, 0.0f));

//    glm::mat4 proj = glm::ortho(0.0f, width * 1.0f, 0.0f, height * 1.0f, -1.0f, 1.0f); // Orthographic Projection
//    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, 0.0f, 0.0f));
//    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(200.0f, 200.0f, 0.0f));

//    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(100.0f, 0.0f, 0.0f));
//    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(-100.0f, -100.0f, 0.0f));

    // Start Center of screen
    hw = this->width * 0.5f; // width/2.0f
    hh = this->height * 0.5f; // height/2.0f
    proj  = glm::ortho(-hw, hw, -hh, hh, -1.0f, 1.0f); // Orthographic Projection
    view  = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

    //glm::mat4 mvp = model * view * proj; // not on screen because it is not reversed from mvp due to opengl and memory layout for math
    glm::mat4 mvp = proj * view * model; // reversed from mvp due to opengl and memory layout for math

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
    //shader->setUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);
    //shader->setUniformMat4f("u_MVP", mvp);

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

    // imgui window clear_color
    ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    glm::vec3 translationA(-350.0f, 0.0f, 0.0f);
    glm::vec3 translationB(350.0f, 0.0f, 0.0f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        renderer.clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        {
            model = glm::translate(glm::mat4(1.0f), translationA);
            mvp = proj * view * model;
            shader->bind();
            shader->setUniformMat4f("u_MVP", mvp);

            renderer.draw(*va, *ib, *shader);
        }

        {
            model = glm::translate(glm::mat4(1.0f), translationB);
            mvp = proj * view * model;
            shader->bind();
            shader->setUniformMat4f("u_MVP", mvp);

            renderer.draw(*va, *ib, *shader);
        }

        // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
        {
            ImGui::SliderFloat("Image 1 - X Translation", &translationA.x, -hw, hw);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("Image 1 - Y Translation", &translationA.y, -hh, hh);            // Edit 1 float using a slider from 0.0f to 1.0f
            //ImGui::SliderFloat("Z Translation", &translation.z, -hz, hz);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("Image 2 - X Translation", &translationB.x, -hw, hw);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::SliderFloat("Image 2 - Y Translation", &translationB.y, -hh, hh);            // Edit 1 float using a slider from 0.0f to 1.0f
            ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

            ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        }

        // Rendering
        ImGui::Render();

        //int display_w, display_h;
        //glfwGetFramebufferSize(window, &display_w, &display_h);
        //glViewport(0, 0, display_w, display_h);
        //glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w);
        //glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}