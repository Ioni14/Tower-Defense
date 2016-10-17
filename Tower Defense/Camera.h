#pragma once

#include <glm/common.hpp>
#include <glm/mat4x4.hpp>

class Camera
{
public:
	explicit Camera(glm::float32 width, glm::float32 height);
	~Camera();

	void setTranslation(glm::vec3 const& dir) {
		m_dirtyViewMatrix = true;
		m_position = -dir;
	}
	void move(glm::vec3 const& dir) {
		m_dirtyViewMatrix = true;
		m_position += -dir;
	}
	void setRotation(glm::float32 angle) {
		m_dirtyViewMatrix = true;
		m_angle = -angle;
	}
	void setScale(glm::vec2 const& scale) {
		m_dirtyViewMatrix = true;
		m_scale = scale;
	}

	glm::mat4 const& getViewMatrix();
	glm::mat4 const& getProjectionMatrix();

	void setWidth(glm::uint32 width) {
		m_dirtyProjectionMatrix = true;
		m_width = static_cast<glm::float32>(width);
	}
	void setHeight(glm::uint32 height) {
		m_dirtyProjectionMatrix = true;
		m_height = static_cast<glm::float32>(height);
	}

private:
	bool m_dirtyViewMatrix; /**< true if the matrix need to be recalculated */
	bool m_dirtyProjectionMatrix;

	glm::float32 m_width;
	glm::float32 m_height;

	glm::vec3 m_position; /**< position in the world */
	glm::float32 m_angle; /**< angle in degrees for rotation */
	glm::vec2 m_scale; /**< scale for size change */
	glm::mat4 m_view; /**< represents the camera transformation (translation, rotation, scaling) */

	glm::mat4 m_projection; /**< how the world is viewed (2D = orthographic, 3D = perspective)*/
};
