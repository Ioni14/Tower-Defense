#pragma once

#include "System.h"

class MovementSystem :
	public System
{
public:
	explicit MovementSystem(EntityManager& entityManager);
	virtual ~MovementSystem();

	virtual void update(float elapsed);
	virtual bool isGranted(Entity const& entity) const;
};
