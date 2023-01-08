#include "VertexArray.hpp"

#include "OpenGLDebug.hpp"

VertexArray::VertexArray() {
	GLCall(glGenVertexArrays(1, &m_rendererID));
}

VertexArray::~VertexArray() {
	GLCall(glDeleteVertexArrays(1, &m_rendererID))
}

void VertexArray::addBuffer(const VertexBuffer& vb, const VertexBufferLayout& layout) {
	bind();
	vb.bind();
	const auto& elements = layout.getElements();
	unsigned char* offset = 0;
	//for (const auto& element : elements) {
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		GLCall(glEnableVertexAttribArray(i));
        GLCall(glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.getStride(), (const void*)offset));
		offset += element.count * VertexBufferElement::getSizeOfType(element.type);
	}
}

void VertexArray::bind() const {
	GLCall(glBindVertexArray(m_rendererID));
}

void VertexArray::unbind() const {
	GLCall(glBindVertexArray(0));
}
