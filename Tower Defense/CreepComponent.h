#pragma once

#include "Component.h"

class CreepComponent :
	public Component
{
public:
	using Ptr = std::unique_ptr<CreepComponent>;

	CreepComponent();
	virtual ~CreepComponent();

	virtual Type getType() const {
		return Type::CREEP;
	}
};
