#pragma once

#include "System.h"

class AITowerSystem :
	public System
{
public:
	explicit AITowerSystem(EntityManager & entityManager);
	virtual ~AITowerSystem();

	virtual void update(float elapsed);
	virtual bool isGranted(Entity const& entity) const;

};

