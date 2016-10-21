#pragma once

#include <vector>
#include <GL/glew.h>

class Texture
{
public:
	Texture();
	explicit Texture(GLuint id, GLuint width, GLuint height);
	~Texture();

	bool isCreated() const;
	void use(GLint index = 0) const;
	static void unuse(GLint index = 0);

	static Texture createFromFile(std::string const & filepath);

	void destroy();

private:
	GLuint m_id;
	GLuint m_width;
	GLuint m_height;
};
