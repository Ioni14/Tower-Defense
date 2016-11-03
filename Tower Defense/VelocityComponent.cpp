#include "VelocityComponent.h"


VelocityComponent::VelocityComponent(glm::vec2 const & velocity, GLfloat speed) :
	m_velocity(velocity),
	m_speed(speed),
	m_movable(true)
{
}

VelocityComponent::~VelocityComponent()
{
}
