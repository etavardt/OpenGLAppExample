#include "OpenGLDebug.hpp"

#include <iostream>
#include <sstream>
#include <GL/glew.h>

void glClearError() {
    while (glGetError() != GL_NO_ERROR);
}

bool glLogCall(const char* function, const char* file, int line) {
    while (GLenum error = glGetError()) {
        std::cout << "[OpenGL Error] (" << error << "): " << function
            << " " << file << ":" << line << std::endl;
        return false;
    }
    return true;
}

namespace glDebug {

#if DEBUG_GL
    static bool g_enable = true;
#else
    static bool g_enable = false;
#endif

    bool isEnabled() {
        return g_enable;
    }

    static void enable() {
        g_enable = true;
    }

    static const char* glGetErrorString(GLenum error) {
        switch (error) {
        case GL_NO_ERROR:          return "GL_NO_ERROR";
        case GL_INVALID_ENUM:      return "GL_INVALID_ENUM";
        case GL_INVALID_VALUE:     return "GL_INVALID_VALUE";
        case GL_INVALID_OPERATION: return "GL_INVALID_OPERATION";
        case GL_STACK_OVERFLOW:    return "GL_STACK_OVERFLOW";
        case GL_STACK_UNDERFLOW:   return "GL_STACK_UNDERFLOW";
        case GL_OUT_OF_MEMORY:     return "GL_OUT_OF_MEMORY";
        default:                   return "(unknown error)";
        }
    }

    void glLogErrorMessage() {
        if (isEnabled()) {
            if (GLenum error = glGetError()) {
                std::cout << "ERROR: " << "GL error: " << error << " = " << glGetErrorString(error) << std::endl;
            }
        }
    }

#ifdef GL_KHR_debug

    static const char* sourceToString(GLenum source) {
        switch (source) {
        case GL_DEBUG_SOURCE_API:             return "API";
        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   return "Window";
        case GL_DEBUG_SOURCE_SHADER_COMPILER: return "Shader";
        case GL_DEBUG_SOURCE_THIRD_PARTY:     return "Third-party";
        case GL_DEBUG_SOURCE_APPLICATION:     return "Application";
        case GL_DEBUG_SOURCE_OTHER:           return "Other";
        default:                                  return "(unknown)";
        }
    }

    static const char* typeToString(GLenum type) {
        switch (type) {
        case GL_DEBUG_TYPE_ERROR:               return "error";
        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: return "deprecated";
        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  return "undefined";
        case GL_DEBUG_TYPE_PORTABILITY:         return "portability";
        case GL_DEBUG_TYPE_PERFORMANCE:         return "performance";
        case GL_DEBUG_TYPE_OTHER:               return "info";
        default:                                return "(unknown)";
        }
    }

    static void GLAPIENTRY callback(GLenum source, GLenum type, GLuint id, GLenum severity,
                                    GLsizei length, const GLchar* message, const void* userParam) {
        std::ostringstream buffer;
        std::string curMessage;
        static std::string prevMessage;

        //const GLchar* end = message + std::strlen(message);
        //while (end != message && (*(end - 1) == '\r' || *(end - 1) == '\n')) {
        //    end--;
        //}

        //buffer << sourceToString(source) << " " << typeToString(type) << " #" << id << ": ";
        //buffer.write(message, end - message);
        buffer << sourceToString(source) << " " << typeToString(type) << " #" << id << ": " << message;

        curMessage = buffer.str();
        if (curMessage != prevMessage) {
            switch (severity) {
            case GL_DEBUG_SEVERITY_HIGH:
                std::cout << "ERROR: " << curMessage << std::endl;
                break;
            case GL_DEBUG_SEVERITY_MEDIUM:
                std::cout << "WARNING: " << curMessage << std::endl;
                break;
            case GL_DEBUG_SEVERITY_LOW:
                std::cout << "INFO: " << curMessage << std::endl;
                break;
            default:
                break;
            }
            prevMessage = curMessage;
        }
    }

    void initialize() {
        if (isEnabled()) {
            GLint majVers = 0, minVers = 0, profile = 0, flags = 0;
            glGetIntegerv(GL_MAJOR_VERSION, &majVers);
            glGetIntegerv(GL_MINOR_VERSION, &minVers);
            glGetIntegerv(GL_CONTEXT_PROFILE_MASK, &profile);
            glGetIntegerv(GL_CONTEXT_FLAGS, &flags);

            bool has_debug = ((majVers > 4) || (majVers == 4 && minVers >= 3));

            if (!has_debug) {
                std::cout << "WARNING: " << "OpenGL debug output not available";
                return;
            }

            glEnable(GL_DEBUG_OUTPUT);
            glDebugMessageCallback(glDebug::callback, nullptr);

            // Forward messages with high severity level
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_HIGH, 0, nullptr, GL_TRUE);

            // Forward messages with medium severity level
            glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DEBUG_SEVERITY_MEDIUM, 0, nullptr, GL_TRUE);

            // Forward messages from the application
            glDebugMessageControl(GL_DEBUG_SOURCE_APPLICATION, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);


            std::string strInitialized("OpenGL debug output enabled");
            glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION, GL_DEBUG_TYPE_OTHER, 1, GL_DEBUG_SEVERITY_LOW,
                                 GLsizei(strInitialized.size()), strInitialized.c_str());
        }
    }

#else // GL_KHR_debug

    void initialize() {
        std::cout << "WARNING: " << "OpenGL debug message output is not supported." << std::endl;
    }

#endif
} // namespace glDebug
