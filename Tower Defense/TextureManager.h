#pragma once

#include <map>
#include <string>
#include "Texture.h"

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	Texture const& getTexture(std::string const& filepath);
private:
	std::map<std::string, Texture> m_textures; /**< [filepath] = Texture */
};
