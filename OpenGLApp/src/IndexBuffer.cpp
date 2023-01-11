#include "IndexBuffer.hpp"

#include <glad/glad.h>
#include "OpenGLDebug.hpp"
#include "Renderer.hpp"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count) : m_count(count) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::IndexBuffer(const std::vector<unsigned int>& vec) : m_count(static_cast<unsigned int>(vec.size())) {
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));

    GLCall(glGenBuffers(1, &m_rendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_count * sizeof(vec[0]), vec.data(), GL_DYNAMIC_DRAW));
}


IndexBuffer::~IndexBuffer() {
    GLCall(glDeleteBuffers(1, &m_rendererID));
}

void IndexBuffer::bind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_rendererID));
}

void IndexBuffer::unbind() const {
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}