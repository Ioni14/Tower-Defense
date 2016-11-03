#pragma once

#include <vector>
#include <GL/glew.h>

class Texture
{
public:
	friend class TextureManager;

	Texture();
	~Texture();

	bool isCreated() const;
	void use(GLint index = 0) const;
	static void unuse(GLint index = 0);

	GLuint getWidth() const {
		return m_width;
	}
	GLuint getHeight() const {
		return m_height;
	}

private:
	explicit Texture(GLuint id, GLuint width, GLuint height);

	static Texture createFromFile(std::string const & filepath);
	void destroy();

private:
	GLuint m_id;
	GLuint m_width;
	GLuint m_height;
};
