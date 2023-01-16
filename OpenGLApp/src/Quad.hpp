#pragma once

#include <array>
#include <vector>

#include "Vertex.hpp"

using Quad = std::array<Vertex, 4>; 
using Quads = std::vector<Quad>;
using VertexBuf = std::vector<float>;
using Indices = std::vector<unsigned int>;

namespace QuadNs {
	Quad createQuad(const float texID = 0.0f, const float mvpID = 0.0f);
	Quads createQuads(const unsigned int quantity, const float texID = 0.0f, const float mvpID = 0.0f);
	VertexBuf getVertexBuf(const Quad& quad, bool bColor = true, bool bTexCoords = true, bool bTexID = true, bool bMvpID = true);
	VertexBuf getVertexBuf(const Quads& quads, bool bColor = true, bool bTexCoords = true, bool bTexID = true, bool bMvpID = true);
	Indices getIndices(const unsigned int quantity = 1);
}