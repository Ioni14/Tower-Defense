#pragma once

#include <glm/common.hpp>
#include "Texture.h"
#include "Tile.h"

class Stage
{
public:
	friend class StageManager;

	Stage();
	~Stage();

	std::vector<Tile>& getTiles() {
		return m_tiles;
	}

	glm::vec2 const& getSpawn() const {
		return m_spawn;
	}

	glm::vec2 const& getFinish() const {
		return m_finish;
	}

	glm::uvec2 const& getSize() const {
		return m_size;
	}

	Texture const& getTileset() const {
		return m_tileset;
	}

	std::vector<glm::vec2> const& getCheckpoints() const {
		return m_checkpoints;
	}
	
	/**
	 * search by any position
	 */
	Tile const * searchTileByPosition(glm::vec2 const & position);

private:
	glm::uvec2 m_size; /**< width x height number of tiles*/
	glm::vec2 m_spawn; /**< world coord of creeps spawn*/
	glm::vec2 m_finish; /**< world coord of creeps finish*/
	std::vector<glm::vec2> m_checkpoints; /**< world coord of creeps checkpoints (between spawn and finish)*/

	std::vector<Tile> m_tiles;

	Texture m_tileset;
};
