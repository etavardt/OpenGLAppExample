#pragma once

#include <vector>

class VertexBuffer {
private:
	unsigned int m_rendererID;
public:
	VertexBuffer(const void* data, size_t size);
	VertexBuffer(const std::vector<float> vec);
	~VertexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int getID() const { return m_rendererID; }
};