#include "Vertex.hpp"

std::array<Vertex, 4> Vertex::CreateQuad(float texID) {
	Vertex v0;
	v0.position = { -0.5f, -0.5f, 0.0f };
	v0.color = { 0.0f, 0.0f, 0.0f, 0.0f };
	v0.texCoords = { 0.0f, 0.0f };
	v0.texID = texID;

	Vertex v1;
	v1.position = { 0.5f, -0.5f, 0.0f };
	v1.color = { 0.0f, 0.0f, 0.0f, 0.0f };
	v1.texCoords = { 1.0f, 0.0f };
	v1.texID = texID;

	Vertex v2;
	v2.position = { 0.5f, 0.5f, 0.0f };
	v2.color = { 0.0f, 0.0f, 0.0f, 0.0f };
	v2.texCoords = { 1.0f, 1.0f };
	v2.texID = texID;

	Vertex v3;
	v3.position = { -0.5f, 0.5f, 0.0f };
	v3.color = { 0.0f, 0.0f, 0.0f, 0.0f };
	v3.texCoords = { 0.0f, 1.0f };
	v3.texID = texID;

	return { v0, v1, v2, v3 };
}
