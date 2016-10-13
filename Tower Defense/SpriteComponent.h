#pragma once

#include "Component.h"

#include <array>
#include <glm/common.hpp>

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	glm::vec2 texCoords;
};

class SpriteComponent :
	public Component
{
public:
	SpriteComponent();
	virtual ~SpriteComponent();

private:
	std::array<Vertex, 4> m_vertices;
	// + texture
};
