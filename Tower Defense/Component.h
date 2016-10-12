#pragma once

class Component
{
public:
	enum class Type { TRANSFORM, VELOCITY };

	Component();
	virtual ~Component();

	virtual Type getType() const = 0;
};
