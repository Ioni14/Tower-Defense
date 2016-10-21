#include "Texture.h"

#include <string>
#include <fstream>
#include <iostream>
#include <sstream>
#include <SFML/Graphics/Image.hpp>

Texture::Texture() :
	Texture(0, 0, 0)
{
}

Texture::Texture(GLuint id, GLuint width, GLuint height) :
	m_id(id),
	m_width(width),
	m_height(height)
{
}

Texture::~Texture()
{
}

bool Texture::isCreated() const
{
	return m_id != 0 && m_width != 0 && m_height != 0;
}

void Texture::use(GLint index) const
{
	if (m_id != 0) {
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}
}

void Texture::unuse(GLint index)
{
	glActiveTexture(GL_TEXTURE0 + index);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture Texture::createFromFile(std::string const & filepath)
{
	Texture texture;

	sf::Image image;
	if (!image.loadFromFile(filepath)) {
		std::cerr << "[Create Texture] error : cannot load image from file " << filepath << std::endl;
		return texture;
	}

	texture.m_width = image.getSize().x;
	texture.m_height = image.getSize().y;

	// create texture object
	glGenTextures(1, &texture.m_id);
	glBindTexture(GL_TEXTURE_2D, texture.m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, texture.m_width, texture.m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}

void Texture::destroy()
{
	if (m_id != 0) {
		glDeleteTextures(1, &m_id);
		m_id = 0;
	}
}
