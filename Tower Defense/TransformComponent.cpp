#include "TransformComponent.h"

#include <iostream>

TransformComponent::TransformComponent() :
	m_dirty(false),
	m_position(0, 0, 0),
	m_angle(0),
	m_scale(1, 1),
	m_matrix()
{
}

TransformComponent::~TransformComponent()
{
}

glm::mat4 const & TransformComponent::getMatrix()
{
	std::cout << "getMatrix()";
	if (m_dirty) {
		m_dirty = false;
		m_matrix = glm::mat4(1.0f);
		m_matrix = glm::translate(m_matrix, m_position);
		m_matrix = glm::rotate(m_matrix, m_angle, glm::vec3(0, 0, 1));
		m_matrix = glm::scale(m_matrix, glm::vec3(m_scale, 1.0f));
		std::cout << " : dirty";
	}
	std::cout << std::endl;
	return m_matrix;
}
