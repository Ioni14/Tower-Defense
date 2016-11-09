#pragma once

#include <memory>

class Component
{
public:
	enum class Type { TRANSFORM, VELOCITY, SPRITE, PATH, ATTACK_TOWER, CARAC };

	Component();
	virtual ~Component();

	virtual Type getType() const = 0;

	virtual void destroy() {}
};
