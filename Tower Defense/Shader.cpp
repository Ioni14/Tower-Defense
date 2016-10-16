#include "Shader.h"

#include <iostream>
#include <string> 
#include <fstream> 
#include <sstream>
#include "glm/gtc/type_ptr.hpp"

Shader::Shader() :
	m_program(0),
	m_shaders()
{
}

bool Shader::addFile(std::string const & filepath, Type type)
{
	if (m_program != 0) {
		std::cerr << "This shader cannot be added because the program is already created !" << std::endl;
		return false;
	}

	auto const& it = m_shaders.find(type);
	if (it != m_shaders.end()) {
		std::cerr << "This type of shader is already added ! " << filepath << std::endl;
		return false;
	}

	GLuint shaderId = glCreateShader(getShaderType(type));

	std::string ossStr;
	{
		std::ifstream shaderFile(filepath);
		if (shaderFile.fail()) {
			std::cerr << "Could not read file " << filepath << " !" << std::endl;
			glDeleteShader(shaderId);
			return false;
		}
		std::ostringstream oss;
		std::string line;
		while (std::getline(shaderFile, line)) {
			oss << line << std::endl;
		}
		ossStr = oss.str();
	}
	const char* strSource(ossStr.c_str());
	glShaderSource(shaderId, 1, &strSource, nullptr); // send source to shader
	glCompileShader(shaderId); // compile shader source

	// checks if the shader has no error
	GLint status;
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetShaderInfoLog(shaderId, infoLogLength, nullptr, strInfoLog);

		std::cerr << "Compile failure in vertex shader " << filepath << " !" << std::endl << strInfoLog << std::endl;
		delete[] strInfoLog;

		glDeleteShader(shaderId);
		return false;
	}

	// puts the shader into map
	m_shaders.insert(std::pair<Type, GLuint>(type, shaderId));

	return true;
}

bool Shader::create()
{
	if (m_program != 0) {
		std::cerr << "This program shader cannot be created twice !" << std::endl;
		return false;
	}
	if (m_shaders.empty()) {
		std::cerr << "There are no shaders to link into program !" << std::endl;
		return false;
	}

	GLuint program = glCreateProgram();
	
	// Attach all the shaders
	for (auto const& shader : m_shaders) {
		glAttachShader(program, shader.second);
	}

	glLinkProgram(program);

	// Checks if the shaders are correctly linked
	GLint status;
	glGetProgramiv(program, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);

		GLchar *strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(program, infoLogLength, nullptr, strInfoLog);

		std::cerr << "Shader program linker failure : " << strInfoLog << std::endl;
		delete[] strInfoLog;

		glDeleteProgram(program);
		return false;
	}

	// Detach all the shaders
	for (auto const& shader : m_shaders) {
		glDetachShader(program, shader.second);
	}

	m_program = program;

	return true;
}

void Shader::destroy()
{
	if (m_program != 0) {
		glDeleteProgram(m_program);
		m_program = 0;
	}

	for (auto const& shader : m_shaders) {
		if (shader.second == 0) {
			continue;
		}
		glDeleteShader(shader.second);
	}
	m_shaders.clear();
}

void Shader::use() const
{
	if (m_program == 0) {
		std::cerr << "No shader program created !" << std::endl;
		return;
	}
	glUseProgram(m_program);
}

void Shader::unuse()
{
	glUseProgram(0);
}

bool Shader::sendFloat(std::string const& name, float value) const
{
	if (m_program == 0) {
		std::cerr << "No shader program created !" << std::endl;
		return false;
	}

	// TODO : Cache locations (quand on rencontre un nouveau "name" on enregistre sa location dans un std::map)
	GLint location = getUniformLocation(name);
	if (location == -1) {
		return false;
	}
	glUniform1f(location, value);
	return true;
}

bool Shader::sendVector2f(std::string const& name, glm::vec2 const& value) const
{
	if (m_program == 0) {
		std::cerr << "No shader program created !" << std::endl;
		return false;
	}

	GLint location = getUniformLocation(name);
	if (location == -1) {
		return false;
	}
	glUniform2f(location, value.x, value.y);
	return true;
}

bool Shader::sendVector3f(std::string const& name, glm::vec3 const& value) const
{
	if (m_program == 0) {
		std::cerr << "No shader program created !" << std::endl;
		return false;
	}

	GLint location = getUniformLocation(name);
	if (location == -1) {
		return false;
	}
	glUniform3f(location, value.x, value.y, value.z);
	return true;
}

bool Shader::sendMatrix4x4(std::string const& name, glm::mat4x4 const& value) const
{
	if (m_program == 0) {
		std::cerr << "No shader program created !" << std::endl;
		return false;
	}

	GLint location = getUniformLocation(name);
	if (location == -1) {
		return false;
	}
	glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(value));
	return true;
}

GLenum Shader::getShaderType(Type type)
{
	switch (type) {
		case Type::VERTEX:
			return GL_VERTEX_SHADER;
		case Type::FRAGMENT:
			return GL_FRAGMENT_SHADER;
		case Type::GEOMETRY:
			return GL_GEOMETRY_SHADER;
	}
	// never here
	return GL_VERTEX_SHADER;
}

GLint Shader::getUniformLocation(std::string const & name) const
{
	GLint location(glGetUniformLocation(m_program, name.c_str()));
	if (location == -1) {
		std::cerr << "There are no location for \"" << name << "\" ! Verify spelling and if it's necessary." << std::endl;
	}
	return location;
}
