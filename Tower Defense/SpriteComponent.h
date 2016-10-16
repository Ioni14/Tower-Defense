#pragma once

#include "Component.h"

#include <array>
#include <glm/common.hpp>
#include <GL/glew.h>

struct Vertex
{
	glm::vec3 position;
	glm::vec4 color;
	//glm::vec2 texCoords;
};

class SpriteComponent :
	public Component
{
public:
	typedef std::unique_ptr<SpriteComponent> Ptr;

	explicit SpriteComponent(float side);
	virtual ~SpriteComponent();

	virtual Type getType() const {
		return Type::SPRITE;
	}

	void draw(bool wireframe = false) const;

private:
	std::array<Vertex, 4> m_vertices;
	// + texture

	GLuint m_vao;
	GLuint m_vboIndices;
	GLuint m_vboVertices;
};
