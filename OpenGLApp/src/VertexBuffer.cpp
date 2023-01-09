#include "VertexBuffer.hpp"

#include <GL/glew.h>
#include "OpenGLDebug.hpp"
#include "Renderer.hpp"

VertexBuffer::VertexBuffer(const void* data, size_t size) {
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

VertexBuffer::VertexBuffer(const std::vector<float> vec) {
    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, vec.size() * sizeof(vec[0]), vec.data(), GL_STATIC_DRAW));
    //GLCall(glBufferData(GL_ARRAY_BUFFER, static_cast<unsigned int>(vec.size()) * sizeof(vec[0]), data, GL_STATIC_DRAW));
}


VertexBuffer::~VertexBuffer() {
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void VertexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_rendererID));
}

void VertexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
}