#pragma once

#include "Component.h"

#include <glm/common.hpp>
#include <glm/geometric.hpp>

class VelocityComponent :
	public Component
{
public:
	typedef std::unique_ptr<VelocityComponent> Ptr;

	explicit VelocityComponent(glm::vec2 const& velocity = glm::vec2(0, 0), glm::vec2 const& speed = glm::vec2(1, 1));
	virtual ~VelocityComponent();

	virtual Type getType() const {
		return Type::VELOCITY;
	}

	glm::vec2 const& getVelocity() const {
		return m_velocity;
	}
	void setVelocity(glm::vec2 const& velocity) {
		m_velocity = velocity;
		if (m_velocity.x != 0 || m_velocity.y != 0) {
			m_velocity = glm::normalize(m_velocity);
		}
		m_velocity *= m_speed;
	}

private:
	glm::vec2 m_velocity;
	glm::vec2 m_speed;
};
