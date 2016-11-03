#pragma once

#include "Component.h"

#include <array>
#include <glm/common.hpp>
#include <GL/glew.h>
#include "Texture.h"

struct Vertex
{
	glm::vec3 position;
	glm::vec3 color;
	glm::vec2 texCoords;
};

class SpriteComponent :
	public Component
{
public:
	typedef std::unique_ptr<SpriteComponent> Ptr;

	explicit SpriteComponent(glm::vec2 const& size, glm::vec2 const& texCoords, Texture const& texture);
	virtual ~SpriteComponent();

	virtual Type getType() const {
		return Type::SPRITE;
	}

	virtual void destroy();

	void setTexture(Texture const& texture);
	Texture const& getTexture() const;
	bool hasTexture() const;
	void draw(bool wireframe = false) const;


private:
	std::array<Vertex, 4> m_vertices;
	Texture m_texture;

	GLuint m_vao;
	GLuint m_vboIndices;
	GLuint m_vboVertices;

	glm::vec2 m_size; /**< size of the shape (frequently 1:1 texels)*/
};
