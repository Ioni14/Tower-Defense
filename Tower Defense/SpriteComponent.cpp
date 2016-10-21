#include "SpriteComponent.h"

#include <iostream>

SpriteComponent::SpriteComponent(glm::vec2 const& size) :
	m_vertices(),
	m_texture(),
	m_vao(0),
	m_vboIndices(0),
	m_vboVertices(0),
	m_size(size)
{
	m_vertices[0].position = glm::vec3(0, 0, 0);
	m_vertices[0].color = glm::vec3(1, 0, 0);
	m_vertices[0].texCoords = glm::vec2(0, 0);

	m_vertices[1].position = glm::vec3(0, -m_size.y, 0);
	m_vertices[1].color = glm::vec3(0, 1, 0);
	m_vertices[1].texCoords = glm::vec2(0, 1);

	m_vertices[2].position = glm::vec3(m_size.x, 0, 0);
	m_vertices[2].color = glm::vec3(0, 0, 1);
	m_vertices[2].texCoords = glm::vec2(1, 0);

	m_vertices[3].position = glm::vec3(m_size.x, -m_size.y, 0);
	m_vertices[3].color = glm::vec3(1, 1, 1);
	m_vertices[3].texCoords = glm::vec2(1, 1);

	unsigned short indicesData[] = {
		0, 1, 2,
		2, 1, 3,
	};

	// on stocke les indices
	glGenBuffers(1, &m_vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	// on enregistre toutes les opérations pour ne pas les réécrire
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

		// on stocke les données graphiques (vertices : positions, colors, texCoords)
		glGenBuffers(1, &m_vboVertices);
		glBindBuffer(GL_ARRAY_BUFFER, m_vboVertices);
			glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(Vertex), &m_vertices[0], GL_STATIC_DRAW);

			glEnableVertexAttribArray(0); // on active le layout location 0 pour les positions
			glEnableVertexAttribArray(1); // on active le layout location 1 pour les colors
			glEnableVertexAttribArray(2); // on active le layout location 2 pour les texCoords

			// 7 * sizeof(float) = il y a 7 floats en tout par vertex (3 pos float + 4 colors float)
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0); // positions = 3 floats par vector
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(3 * sizeof(GLfloat))); // colors = 3 floats par vector. après les 3 floats de position
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(6 * sizeof(GLfloat))); // texCoords = 2 floats par vector. après les 3 pos + 3 colors

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vboIndices);

		glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind : on n'utilise plus ce buffer

	glBindVertexArray(0);
}

SpriteComponent::SpriteComponent(GLfloat width, GLfloat height) :
	SpriteComponent(glm::vec2(width, height))
{
}

SpriteComponent::~SpriteComponent()
{
	m_texture.destroy();
	glDeleteBuffers(1, &m_vboIndices);
	glDeleteBuffers(1, &m_vboVertices);
	glDeleteVertexArrays(1, &m_vao);
}

void SpriteComponent::setTexture(Texture const & texture)
{
	m_texture = texture;
}

Texture const & SpriteComponent::getTexture() const
{
	return m_texture;
}

bool SpriteComponent::hasTexture() const
{
	return m_texture.isCreated();
}

void SpriteComponent::draw(bool wireframe) const
{
	glBindVertexArray(m_vao);
	if (wireframe) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
	}
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0); // indexed
	glBindVertexArray(0);
}
