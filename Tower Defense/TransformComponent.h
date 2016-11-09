#pragma once

#include "Component.h"

#include <iostream>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class TransformComponent :
	public Component
{
public:
	typedef std::unique_ptr<TransformComponent> Ptr;

	TransformComponent();
	explicit TransformComponent(glm::vec3 const& pos, GLfloat angle = 0.0f, glm::vec2 const& scale = glm::vec2(1.0f, 1.0f));
	virtual ~TransformComponent();

	virtual Type getType() const {
		return Type::TRANSFORM;
	}

	glm::vec3 const& getPosition() const {
		return m_position;
	}
	void setTranslation(glm::vec3 const& pos) {
		m_dirty = true;
		m_position = pos;
	}
	void move(glm::vec3 const& dir) {
		m_dirty = true;
		m_position += dir;
	}
	void setRotation(GLfloat angle) {
		m_dirty = true;
		m_angle = angle;
	}
	void setScale(glm::vec2 const& scale) {
		m_dirty = true;
		m_scale = scale;
	}

	glm::mat4 const& getMatrix();

private:
	bool m_dirty; /**< true if the matrix need to be recalculated */

	glm::vec3 m_position; /**< position in the world */
	GLfloat m_angle; /**< angle in degrees for rotation */
	glm::vec2 m_scale; /**< scale for size change */
	glm::mat4 m_matrix; /**< represents the model transformation (translation, rotation, scaling) */
};
