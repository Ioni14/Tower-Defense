#pragma once

#include <map>
#include <GL/glew.h>
#include <glm/common.hpp>

class Shader
{
public:
	enum class Type { VERTEX, FRAGMENT, GEOMETRY };

	Shader();

	bool addFile(std::string const& filepath, Type type);
	bool create();
	void destroy();

	void use() const;
	static void unuse();

	bool sendFloat(std::string const& name, GLfloat value) const;
	bool sendVector2f(std::string const& name, glm::vec2 const& value) const;
	bool sendVector3f(std::string const& name, glm::vec3 const& value) const;
	bool sendMatrix4x4(std::string const& name, glm::mat4x4 const& value) const;
	bool sendTexture(std::string const& name, GLint const& value) const;

private:
	static GLenum getShaderType(Type type);
	GLint getUniformLocation(std::string const& name) const;

private:
	GLuint m_program;
	std::map<Type, GLuint> m_shaders;
};
