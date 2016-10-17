#include "Camera.h"

#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::float32 width, glm::float32 height) :
	m_dirtyViewMatrix(true),
	m_dirtyProjectionMatrix(true),
	m_width(width),
	m_height(height),
	m_position(0, 0, 0),
	m_angle(0),
	m_scale(1, 1),
	m_view(1.0f),
	m_projection(1.0f)
{
}

Camera::~Camera()
{
}

glm::mat4 const & Camera::getProjectionMatrix()
{
	if (m_dirtyProjectionMatrix) {
		m_dirtyProjectionMatrix = false;
		m_projection = glm::ortho(0.0f, m_width, 0.0f, m_height);
	}
	return m_projection;
}

glm::mat4 const & Camera::getViewMatrix()
{
	if (m_dirtyViewMatrix) {
		m_dirtyViewMatrix = false;
		m_view = glm::mat4(1.0f);
		m_view = glm::translate(m_view, m_position);
		m_view = glm::rotate(m_view, m_angle, glm::vec3(0, 0, 1));
		m_view = glm::scale(m_view, glm::vec3(m_scale, 1.0f));
	}
	return m_view;
}
