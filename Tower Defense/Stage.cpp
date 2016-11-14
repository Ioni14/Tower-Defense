#include "Stage.h"

Stage::Stage()
{
}

Stage::~Stage()
{
}

Tile const * Stage::searchTileByPosition(glm::vec2 const & position)
{
	for (auto& tile : m_tiles) {
		auto const& tileSize = tile.getSprite().getSize();
		auto const& tilePosition = tile.getTransform().getPosition();

		if (position.x >= tilePosition.x && position.x < tilePosition.x + tileSize.x
			&& position.y <= tilePosition.y && position.y > tilePosition.y - tileSize.y) {
			return &tile;
		}
	}
	return nullptr;
}
