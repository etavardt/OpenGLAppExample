#pragma once

#include <array>

#include <glm/glm.hpp>

struct Vertex {
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoords;
	float texID;
	float mvpID;
//	float position[3];
//	float color[4];
//	float texCoords[2];
//	float texID;

	static std::array<Vertex, 4> CreateQuad(float texID, float mvpID);
};