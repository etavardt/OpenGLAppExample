#include "OpenGLWindow.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include "OpenGLDebug.hpp"
#include "Renderer.hpp"
#include "VertexBuffer.hpp"
#include "IndexBuffer.hpp"

struct ShaderProgramSource {
    std::string vertexSource;
    std::string fragmentSource;
};

static ShaderProgramSource ParseShader(const std::string& filepath) {
    std::ifstream stream(filepath);
    std::stringstream ss[2];

    enum class ShaderType {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1
    };

    ShaderType type = ShaderType::NONE;

    std::string line;
    while (getline(stream, line)) {
        if (line.find("#shader") != std::string::npos) {
            if (line.find("vertex") != std::string::npos) {
                type = ShaderType::VERTEX;
            } else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        } else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

static int CompileShader(GLuint type, const std::string& source) {
    //std::assert(source);
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));
 
    //Syntax checking and Error handling
    GLint result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));

    GLint length;
    if (result == GL_FALSE) {
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));

        GLCall(glGetShaderInfoLog(id, length, &length, message));
        std::cout << "Faild to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        GLCall(glDeleteShader(id));
        return 0;
    }

    return id;
}
static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLuint progId = glCreateProgram();
    GLuint vshaderId = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fshaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    GLCall(glAttachShader(progId, vshaderId));
    GLCall(glAttachShader(progId, fshaderId));
    GLCall(glLinkProgram(progId));
    GLCall(glValidateProgram(progId));

    //GLCall(glDetachShader(progId, vshaderId));
    //GLCall(glDetachShader(progId, fshaderId));

    GLCall(glDeleteShader(vshaderId));
    GLCall(glDeleteShader(fshaderId));

    return progId;
}

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
    //std::cout << "OpenGLWindow Constructed" << std::endl;
}

OpenGLWindow::~OpenGLWindow() {
    delete ib;
    delete vb;
    GLCall(glDeleteProgram(shader));
    glfwTerminate();

    //std::cout << "OpenGLWindow Destructed" << std::endl;
}

void OpenGLWindow::init() {
    std::cout << glGetString(GL_VERSION) << std::endl;

    GLCall(glGenVertexArrays(1, &vao));
    GLCall(glBindVertexArray(vao));

//    VertexBuffer vb(vertexBuf, sizeof(vertexBuf));

    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2 , 0));

//    IndexBuffer ib(indices, 6);

    ShaderProgramSource source = ParseShader("res/shaders/basic.shader");

    std::cout << "VERTEX SHADER" << std::endl;
    std::cout << source.vertexSource << std::endl;
    std::cout << "FRAGMENT SHADER" << std::endl;
    std::cout << source.fragmentSource << std::endl;

    shader = CreateShader(source.vertexSource, source.fragmentSource);
    GLCall(glUseProgram(shader));

    cLoc = glGetUniformLocation(shader, "u_Color");
    ASSERT(cLoc != -1);
    GLCall(glUniform4f(cLoc, 0.8f, 0.3f, 0.8f, 1.0f));

    //unbind for vertex array example from The Cherno's YT chnl
    GLCall(glBindVertexArray(0));
    GLCall(glUseProgram(0));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));


}

void OpenGLWindow::pullEvents() {
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glUniform4f(cLoc, r, 0.3f, 0.8f, 1.0f);

        glBindVertexArray(vao);
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