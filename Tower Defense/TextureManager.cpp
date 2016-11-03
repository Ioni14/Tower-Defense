#include "TextureManager.h"

TextureManager::TextureManager() :
	m_textures()
{
}

TextureManager::~TextureManager()
{
	for (auto& it = m_textures.begin(); it != m_textures.end();) {
		it->second.destroy();
		it = m_textures.erase(it);
	}
}

Texture const & TextureManager::getTexture(std::string const & filepath)
{
	{
		auto const& it = m_textures.find(filepath);
		if (it != m_textures.end()) {
			// texture exists
			return it->second;
		}
	}

	// texture missed : add the texture
	m_textures.insert(std::pair<std::string, Texture>(filepath, Texture::createFromFile(filepath)));
	auto const& it = m_textures.find(filepath);
	return it->second;
}
