#pragma once

#include "Component.h"

#include <memory>
#include <glm/common.hpp>
#include <glm/geometric.hpp>

class VelocityComponent :
	public Component
{
public:
	typedef std::unique_ptr<VelocityComponent> Ptr;

	VelocityComponent();
	VelocityComponent(glm::vec2 const& velocity);
	virtual ~VelocityComponent();

	virtual Type getType() const {
		return Type::VELOCITY;
	}

	glm::vec2 const& getVelocity() const {
		return m_velocity;
	}
	void setVelocity(glm::vec2 const& velocity) {
		m_velocity = glm::normalize(velocity);
	}

private:
	glm::vec2 m_velocity;
};
