#include "Tile.h"

Tile::Tile(glm::vec2 const& size, glm::vec2 const& position, glm::vec2 const& texCoords, Texture const& texture) :
	m_sprite(size, texCoords, texture),
	m_transform()
{
	m_transform.setTranslation(glm::vec3(position, 1.0f));
}

Tile::~Tile()
{
}
