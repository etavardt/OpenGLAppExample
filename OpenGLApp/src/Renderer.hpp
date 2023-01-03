#pragma once

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer {
private:
public:
	inline void clear() const {
		GLCall(glClear(GL_COLOR_BUFFER_BIT));
	}
	void draw(const VertexArray& va, const IndexBuffer&ib, const Shader& shader) const;
};