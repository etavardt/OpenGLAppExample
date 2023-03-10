#include "OpenGLWindow.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>

#include "OpenGLDebug.hpp"
#include "KewlF/Logger.hpp"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "Test.hpp"
#include "TestClearColor.hpp"
#include "TestTexture2D.hpp"
#include "Test2DBatchRendering.hpp"
#include "TestViewImage.hpp"

OpenGLWindow::OpenGLWindow() : m_width(1680), m_height(945) {

    glfwSetErrorCallback(error_callback);

    /* Initialize the library */
    if (!glfwInit())
        throw "Failed call to glfwInit";

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    m_window = glfwCreateWindow(m_width, m_height, "OpenGL", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        throw "Failed call to glfwCreateWindow";
    }
    
    glfwSetKeyCallback(m_window, key_callback);

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

    glfwSwapInterval(1);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        throw "Failed call to gladLoadGLLoader!";
    }

    glDebug::initialize();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(m_window, true);
    const char* glsl_version = "#version 130";
    ImGui_ImplOpenGL3_Init(glsl_version);

  
    //std::cout << "OpenGLWindow Constructed" << std::endl;
}

OpenGLWindow::~OpenGLWindow() {
    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(m_window);
    glfwTerminate();

    //std::cout << "OpenGLWindow Destructed" << std::endl;
}

void OpenGLWindow::init() {
    LOG(INFO) << glGetString(GL_VERSION) << std::endl;

}

void OpenGLWindow::pullEvents() {
    Renderer renderer;
    test::Test* currentTest = nullptr;
    test::TestMenu* testMenu = new test::TestMenu(currentTest);
    currentTest = testMenu;

    testMenu->RegisterTest<test::TestClearColor>("Clear Color");
    testMenu->RegisterTest<test::TestTexture2D>("2D Texture");
    testMenu->RegisterTest<test::Test2DBatchRendering>("2D BatchRendering");
    testMenu->RegisterTest<test::TestViewImage>("View Image");

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(m_window))
    {
        GLCall(glClearColor(0.0f, 0.0f, 0.0f, 0.0f));
        renderer.clear();

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        if (currentTest) {
            currentTest->onUpdate(0.0f);
            currentTest->onRender();
            ImGui::Begin("Test");
            if (currentTest != testMenu && ImGui::Button("<-")) {
                delete currentTest;
                currentTest = testMenu;
            }
            currentTest->onImGuiRender();
            ImGui::End();
        }

        // Rendering
        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        /* Swap front and back buffers */
        GLCall(glfwSwapBuffers(m_window));

        /* Poll for and process events */
        GLCall(glfwPollEvents());
    }
    if (currentTest != testMenu) {
        delete currentTest;
    }
    delete testMenu;
}