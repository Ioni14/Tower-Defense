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
	void use() const;
	static void unuse();

	static Texture createFromFile(std::string const & filepath);

private:
	GLuint m_id;
	GLuint m_width;
	GLuint m_height;
};
