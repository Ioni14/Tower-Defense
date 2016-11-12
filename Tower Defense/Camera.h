#pragma once

#include <glm/common.hpp>
#include <glm/mat4x4.hpp>
#include <GL/glew.h>

class Camera
{
public:
	explicit Camera(GLfloat width, GLfloat height);
	~Camera();

	void setTranslation(glm::vec3 const& dir) {
		m_dirtyViewMatrix = true;
		m_position = -dir;
	}
	void move(glm::vec3 const& dir) {
		m_dirtyViewMatrix = true;
		m_position += -dir;
	}
	void setRotation(GLfloat angle) {
		m_dirtyViewMatrix = true;
		m_angle = -angle;
	}
	void setScale(glm::vec2 const& scale) {
		m_dirtyViewMatrix = true;
		m_scale = scale;
	}

	glm::mat4 const& getViewMatrix();
	glm::mat4 const& getProjectionMatrix();

	void setWidth(GLfloat width) {
		m_dirtyProjectionMatrix = true;
		m_width = width;
	}
	void setHeight(GLfloat height) {
		m_dirtyProjectionMatrix = true;
		m_height = height;
	}

	glm::vec2 screenToWorld(glm::vec2 const& position);

private:
	bool m_dirtyViewMatrix; /**< true if the matrix need to be recalculated */
	bool m_dirtyProjectionMatrix;

	GLfloat m_width;
	GLfloat m_height;

	glm::vec3 m_position; /**< position in the world */
	GLfloat m_angle; /**< angle in degrees for rotation */
	glm::vec2 m_scale; /**< scale for size change */
	glm::mat4 m_view; /**< represents the camera transformation (translation, rotation, scaling) */

	glm::mat4 m_projection; /**< how the world is viewed (2D = orthographic, 3D = perspective)*/
};
