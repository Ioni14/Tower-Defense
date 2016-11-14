#pragma once

#include <glm/common.hpp>
#include "SpriteComponent.h"
#include "TransformComponent.h"

class Tile
{
public:
	Tile(glm::vec2 const& size, glm::vec2 const& position, glm::vec2 const& texCoords, Texture const& texture);
	virtual ~Tile();

	SpriteComponent& getSprite() {
		return m_sprite;
	}

	TransformComponent& getTransform() {
		return m_transform;
	}

	TransformComponent const& getTransform() const {
		return m_transform;
	}

private:
	SpriteComponent m_sprite;
	TransformComponent m_transform;
};
