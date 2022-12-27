#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "OpenGLWindow.hpp"

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
    //ShaderProgramSource sps;
    //sps.vertexSource = ss[0].str();
    //sps.fragmentSource = ss[1].str();
    return { ss[0].str(), ss[1].str() };
}

static int CompileShader(GLuint type, const std::string& source) {
    //std::assert(source);
    GLuint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
 
    //TODO: Syntax checking and Error handling
    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    GLint length;
    if (result == GL_FALSE) {
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));

        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Faild to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
    GLuint progId = glCreateProgram();
    GLuint vshaderId = CompileShader(GL_VERTEX_SHADER, vertexShader);
    GLuint fshaderId = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(progId, vshaderId);
    glAttachShader(progId, fshaderId);
    glLinkProgram(progId);
    glValidateProgram(progId);

    //glDetachShader(progId, vshaderId);
    //glDetachShader(progId, fshaderId);

    glDeleteShader(vshaderId);
    glDeleteShader(fshaderId);

    return progId;
}

OpenGLWindow::OpenGLWindow() {
    /* Initialize the library */
    if (!glfwInit())
        throw "Failed call to glfwInit";

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1820, 1440, "OpenGL", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        throw "Failed call to glfwCreateWindow";
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "glewInit Failed" << std::endl;
    }

    std::cout << "OpenGLWindow Constructed" << std::endl;
}

OpenGLWindow::~OpenGLWindow() {
    glDeleteProgram(shader);
    glfwTerminate();

    std::cout << "OpenGLWindow Destructed" << std::endl;
}

void OpenGLWindow::init() {
    std::cout << glGetString(GL_VERSION) << std::endl;

    float triVertexBuf[6] = {
        -0.5f, -0.5f,
         0.0f,  0.5f,
         0.5f, -0.5f
    };
    glGenBuffers(bufNamesSize, bufNames);
    glBindBuffer(GL_ARRAY_BUFFER, *bufNames);
    //glGenBuffers(bufNamesSize, &bufNames);
    //glBindBuffer(GL_ARRAY_BUFFER, bufNames);
    glBufferData(GL_ARRAY_BUFFER, sizeof(triVertexBuf), triVertexBuf ,GL_STATIC_DRAW);
    //glBufferData(GL_ARRAY_BUFFER, 6*sizeof(float), triVertexBuf, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    // glVertexAttribPointer(GLuint index,
    //    GLint size,
    //    GLenum type,
    //    GLboolean normalized,
    //    GLsizei stride,
    //    const GLvoid * pointer);
    //glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(triVertexBuf)/3, 0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2 , 0);

    //ShaderProgramSource source = ParseShader("res/shaders/basicRedTri.shader");
    ShaderProgramSource source = ParseShader("res/shaders/basicBlueTri.shader");

    std::cout << "VERTEX SHADER" << std::endl;
    std::cout << source.vertexSource << std::endl;
    std::cout << "FRAGMENT SHADER" << std::endl;
    std::cout << source.fragmentSource << std::endl;

    //GLuint shader = CreateShader(vertexShader, fragmentShader);
    shader = CreateShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLWindow::pullEvents() {
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        //glDrawArrays(GL_TRIANGLES, bufNames[0], 3);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }
}