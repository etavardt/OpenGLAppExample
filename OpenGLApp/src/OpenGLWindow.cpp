#include <GL\glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <assert.h>
#include "OpenGLWindow.hpp"
#include "OpenGLDebug.hpp"


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
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);
 
    //Syntax checking and Error handling
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

    glfwSwapInterval(1);

    if (glewInit() != GLEW_OK) {
        std::cerr << "glewInit Failed" << std::endl;
    }
    glDebug::initialize();

    std::cout << "OpenGLWindow Constructed" << std::endl;
}

OpenGLWindow::~OpenGLWindow() {
    glDeleteProgram(shader);
    glfwTerminate();

    std::cout << "OpenGLWindow Destructed" << std::endl;
}

void OpenGLWindow::init() {
    std::cout << glGetString(GL_VERSION) << std::endl;

    //Vertex Buffer
    float vertexBuf[] = {
        -0.5f, -0.5f, //0
         0.5f, -0.5f, //1
         0.5f,  0.5f, //2
        -0.5f,  0.5f  //3
    };

    //Indices buffer
    unsigned int indices[] = {
        0,1,2,
        2,3,0
    };

    glGenBuffers(bufNamesSize, bufNames);
    glBindBuffer(GL_ARRAY_BUFFER, *bufNames);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBuf), vertexBuf,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2 , 0);

    unsigned int ibo;
    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //ShaderProgramSource source = ParseShader("res/shaders/basicRedTri.shader");
    ShaderProgramSource source = ParseShader("res/shaders/basic.shader");

    std::cout << "VERTEX SHADER" << std::endl;
    std::cout << source.vertexSource << std::endl;
    std::cout << "FRAGMENT SHADER" << std::endl;
    std::cout << source.fragmentSource << std::endl;

    shader = CreateShader(source.vertexSource, source.fragmentSource);
    glUseProgram(shader);

    cLoc = glGetUniformLocation(shader, "u_Color");
    assert(cLoc != -1);
    glUniform4f(cLoc, 0.8f, 0.3f, 0.8f, 1.0f);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLWindow::pullEvents() {
    float r = 0.0f;
    float increment = 0.05f;
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        glUniform4f(cLoc, r, 0.3f, 0.8f, 1.0f);

        //glDrawArrays(GL_TRIANGLES, bufNames[0], 3);
        //glDrawArrays(GL_TRIANGLES, 0, 6);
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