#include "Renderer.hpp"

#include "OpenGLDebug.hpp"

void Renderer::draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const {
	shader.bind();
	va.bind();
	ib.bind();
	//GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_UNSIGNED_INT, nullptr));
	GLCall(glDrawElements(GL_TRIANGLES, ib.getCount(), GL_INT, nullptr)); // Test for Error
}

void Renderer::clear() const {
	glClear(GL_COLOR_BUFFER_BIT);
}