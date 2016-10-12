#include "VelocityComponent.h"



VelocityComponent::VelocityComponent() :
	m_velocity(0, 0)
{
}

VelocityComponent::VelocityComponent(glm::vec2 const & velocity) :
	m_velocity(velocity)
{
	m_velocity = glm::normalize(m_velocity);
}


VelocityComponent::~VelocityComponent()
{
}
