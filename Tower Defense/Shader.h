#pragma once

#include <map>
#include <GL/glew.h>
#include <SFML/Graphics.hpp>

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

	bool sendFloat(std::string const& name, float value) const;
	bool sendVector2f(std::string const& name, sf::Vector2f const& value) const;
	bool sendVector3f(std::string const& name, sf::Vector3f const& value) const;

private:
	static GLenum getShaderType(Type type);
	GLint getUniformLocation(std::string const& name) const;

private:
	GLuint m_program;
	std::map<Type, GLuint> m_shaders;
};
