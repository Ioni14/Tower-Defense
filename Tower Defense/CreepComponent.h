#pragma once

#include "Component.h"

class CreepComponent :
	public Component
{
public:
	CreepComponent();
	virtual ~CreepComponent();

	virtual Type getType() const {
		return Type::CREEP;
	}
};
