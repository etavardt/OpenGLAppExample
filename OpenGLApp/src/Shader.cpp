#include "Shader.hpp"

#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "OpenGLDebug.hpp"

Shader::Shader() : m_RendererID(0) {

}

Shader::Shader(const std::string& filepath) : m_Filepath(filepath), m_RendererID(0) {
    ShaderProgramSource source = ParseShader(filepath);
    //std::cout << "VERTEX SHADER" << std::endl;
    //std::cout << source.vertexSource << std::endl;
    //std::cout << "FRAGMENT SHADER" << std::endl;
    //std::cout << source.fragmentSource << std::endl;
    m_RendererID = CreateShader(source.vertexSource, source.fragmentSource);

}

Shader::~Shader() {
    GLCall(glDeleteProgram(m_RendererID));
}

void Shader::bind() const {
    GLCall(glUseProgram(m_RendererID));
}

void Shader::unbind() const {
    GLCall(glUseProgram(0));
}

// Set uniforms
void Shader::setUniform1i(const std::string& name, int value) {
    GLCall(glUniform1i(getUniformLocation(name), value));
}

void Shader::setUniform1f(const std::string& name, float value) {
    GLCall(glUniform1f(getUniformLocation(name), value));
}

void Shader::setUniform4f(const std::string& name, float v0, float v1, float v2, float v3) {
    GLCall(glUniform4f(getUniformLocation(name), v0, v1, v2, v3));
}

void Shader::setUniformMat4f(const std::string& name, const glm::mat4& matrix) {
    GLCall(glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, &matrix[0][0]));
}


int Shader::getUniformLocation(const std::string& name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
    if (location == -1) {
        std::cout << "WARNING: uniform '" << name << "' doesn't exist!" << std::endl;
    }
    m_UniformLocationCache[name] = location;

    return location;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath) {
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
            }
            else if (line.find("fragment") != std::string::npos) {
                type = ShaderType::FRAGMENT;
            }
        }
        else {
            ss[(int)type] << line << "\n";
        }
    }

    return { ss[0].str(), ss[1].str() };
}

int Shader::CompileShader(unsigned int type, const std::string& source) {
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

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader) {
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