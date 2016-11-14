#include "TransformComponent.h"

TransformComponent::TransformComponent() :
	TransformComponent(glm::vec3(0.0f, 0.0f, 0.0f))
{
}

TransformComponent::TransformComponent(glm::vec3 pos, GLfloat angle, glm::vec2 scale) :
	m_dirty(true),
	m_position(pos),
	m_angle(angle),
	m_scale(scale),
	m_matrix(1.0f)
{
}

TransformComponent::~TransformComponent()
{
}

glm::mat4 const & TransformComponent::getMatrix()
{
	if (m_dirty) {
		m_dirty = false;
		m_matrix = glm::mat4(1.0f);
		m_matrix = glm::translate(m_matrix, m_position);
		m_matrix = glm::rotate(m_matrix, m_angle, glm::vec3(0, 0, 1));
		m_matrix = glm::scale(m_matrix, glm::vec3(m_scale, 1.0f));
	}
	return m_matrix;
}
