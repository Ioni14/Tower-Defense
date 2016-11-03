#pragma once

#include "Component.h"

#include <glm/common.hpp>
#include <glm/geometric.hpp>
#include <GL/glew.h>

class VelocityComponent :
	public Component
{
public:
	typedef std::unique_ptr<VelocityComponent> Ptr;

	explicit VelocityComponent(glm::vec2 const& velocity = glm::vec2(0, 0), GLfloat speed = 1.0f);
	virtual ~VelocityComponent();

	virtual Type getType() const {
		return Type::VELOCITY;
	}

	glm::vec2 getVelocity() const {
		if (!m_movable) {
			return glm::vec2(0, 0);
		}

		glm::vec2 vel(m_velocity);
		if (vel.x != 0 || vel.y != 0) {
			vel = glm::normalize(vel);
		}

		return vel * m_speed;
	}
	void setVelocity(glm::vec2 const& velocity) {
		m_velocity = velocity;
	}

	GLfloat getSpeed() const {
		if (!m_movable) {
			return 0.0f;
		}

		return m_speed;
	}
	void setSpeed(GLfloat speed) {
		m_speed = speed;
	}

	bool isMovable() const {
		return m_movable;
	}
	void setMovable(bool movable) {
		m_movable = movable;
	}

private:
	glm::vec2 m_velocity;
	GLfloat m_speed;
	bool m_movable;
};
