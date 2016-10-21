#pragma once

#include <glm/common.hpp>
#include "Texture.h"
#include "SpriteComponent.h"

class Stage
{
public:
	friend class StageManager;

	Stage();
	~Stage();
private:
	glm::uvec2 m_size; /**< width x height number of tiles*/
	glm::vec2 m_spawn; /**< world coord of creeps spawn*/

	std::vector<SpriteComponent> m_tiles;

	Texture m_tileset;
};
