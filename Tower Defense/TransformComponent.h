#pragma once

#include "Component.h"

#include <memory>
#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>

class TransformComponent :
	public Component
{
public:
	typedef std::unique_ptr<TransformComponent> Ptr;

	TransformComponent();
	virtual ~TransformComponent();

	virtual Type getType() const {
		return Type::TRANSFORM;
	}

	void setTranslation(glm::vec3 const& dir) {
		m_dirty = true;
		m_position = dir;
	}
	void move(glm::vec3 const& dir) {
		m_dirty = true;
		m_position += dir;
	}
	void setRotation(glm::float32 angle) {
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
	glm::float32 m_angle; /**< angle in degrees for rotation */
	glm::vec2 m_scale; /**< scale for size change */
	glm::mat4 m_matrix; /**< represents the model transformation (translation, rotation, scaling) */
};
