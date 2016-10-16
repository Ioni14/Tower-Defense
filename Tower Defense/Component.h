#pragma once

#include <memory>

class Component
{
public:
	enum class Type { TRANSFORM, VELOCITY, SPRITE };

	Component();
	virtual ~Component();

	virtual Type getType() const = 0;
};
