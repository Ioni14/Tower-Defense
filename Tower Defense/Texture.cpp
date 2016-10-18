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
	if (m_id != 0) {
		glDeleteTextures(1, &m_id);
	}
}

bool Texture::isCreated() const
{
	return m_id != 0 && m_width != 0 && m_height != 0;
}

void Texture::use() const
{
	if (m_id != 0) {
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_id);
	}
}

void Texture::unuse()
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

Texture Texture::createFromFile(std::string const & filepath)
{
	Texture texture;
	/*
	std::ifstream file(filepath, std::ifstream::binary);
	if (file.fail()) {
		std::cerr << "[Create Texture] error : cannot open file " << filepath << std::endl;
		return Texture();
	}

	// compute size
	file.seekg(0, std::ios_base::end);
	auto size = file.tellg();
	file.seekg(0, std::ios_base::beg);

	// read full file
	std::vector<GLchar> buffer;
	buffer.resize(size);
	file.read(&buffer[0], size);

	if (file.fail()) {
		std::cerr << "[Create Texture] error : only " << file.gcount() << " could be read" << std::endl;
		buffer.resize(0);
		return Texture();
	}

	file.close();
	*/

	// read file + decode png file

	sf::Image image;
	if (!image.loadFromFile(filepath)) {
		std::cerr << "[Create Texture] error : cannot load image from file " << filepath << std::endl;
		return texture;
	}

	texture.m_width = image.getSize().x;
	texture.m_height = image.getSize().y;

	//decode
	/*
	GLuint error = lodepng::decode(image, texture.m_width, texture.m_height, filepath);
	if (error != 0) {
		std::cerr << "[Create Texture] decoder error " << error << " : " << lodepng_error_text(error) << std::endl;
		return texture;
	}
	*/

	// create texture object
	glGenTextures(1, &texture.m_id);
	glBindTexture(GL_TEXTURE_2D, texture.m_id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture.m_width, texture.m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image.getPixelsPtr());

	glBindTexture(GL_TEXTURE_2D, 0);

	return texture;
}
