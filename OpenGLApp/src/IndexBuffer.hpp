#pragma once

#include <vector>

class IndexBuffer {
private:
	unsigned int m_rendererID;
	unsigned int m_count;
public:
	IndexBuffer(const unsigned int* data, unsigned int count);
	IndexBuffer(const std::vector<unsigned int>& vec);
	~IndexBuffer();

	void bind() const;
	void unbind() const;

	inline unsigned int getCount() const { return m_count; }
};