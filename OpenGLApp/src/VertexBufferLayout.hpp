#pragma once

#include <vector>
#include <GL/glew.h>
#include "OpenGLDebug.hpp"

struct VertexBufferElement {
	unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int getSizeOfType(unsigned int type) {
		switch (type) {
			case GL_FLOAT : return 4;
			case GL_UNSIGNED_INT: return 4;
			case GL_UNSIGNED_BYTE: return 1;
		}
		ASSERT(false);
		return 0;
	}
};

class VertexBufferLayout {
private:
	std::vector<VertexBufferElement> m_elements;
	unsigned int m_Stride;
public:
	VertexBufferLayout() : m_Stride(0) {}
	~VertexBufferLayout() {};

	template<typename T>
	void push(unsigned int count) {
		assert(false);
	}

	template<>
	void push<float>(unsigned int count) {
		m_elements.push_back(VertexBufferElement(GL_FLOAT, count, GL_FALSE));
		//m_Elements.push_back({GL_FLOAT, count, GL_FALSE});
		m_Stride += count * sizeof(GLfloat);
	}
	template<>
	void push<unsigned int>(unsigned int count) {
		//m_Elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
		m_elements.push_back(VertexBufferElement(GL_UNSIGNED_INT, count, GL_FALSE));
		m_Stride += count * sizeof(GLuint);
	}
	template<>
	void push<unsigned char>(unsigned int count) {
		m_elements.push_back(VertexBufferElement(GL_UNSIGNED_BYTE, count, GL_TRUE));
		//m_Elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
		m_Stride += count * sizeof(GLbyte);
	}

	inline const std::vector<VertexBufferElement>& getElements() const { return m_elements; }
	inline const unsigned int getStride() const { return m_Stride; }
};