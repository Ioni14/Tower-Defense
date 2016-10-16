#include "VelocityComponent.h"


VelocityComponent::VelocityComponent(glm::vec2 const & velocity, glm::vec2 const & speed) :
	m_velocity(velocity),
	m_speed(speed)
{
	setVelocity(m_velocity);
}

VelocityComponent::~VelocityComponent()
{
}
