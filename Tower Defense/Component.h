#pragma once

#include <memory>

class Component
{
public:
	enum class Type { TRANSFORM, VELOCITY, SPRITE, PATH };

	Component();
	virtual ~Component();

	virtual Type getType() const = 0;

	virtual void destroy() {}
};
