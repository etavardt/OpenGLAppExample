#pragma once

#include "VertexArray.hpp"
#include "IndexBuffer.hpp"
#include "Shader.hpp"

class Renderer {
private:
public:
	void clear() const;
	void draw(const VertexArray& va, const IndexBuffer&ib, const Shader& shader) const;
};