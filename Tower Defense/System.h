#pragma once

#include <vector>
#include "Entity.h"
#include "EntityManager.h"

class System
{
public:
	explicit System(EntityManager& entityManager);
	virtual ~System();

	void registerEntity(Entity entity);
	void unregisterEntity(Entity entity);

	virtual void update(float elapsed) = 0;
	virtual bool isGranted(Entity const& entity) const = 0;

protected:
	EntityManager& m_entityManager;
	std::vector<Entity> m_entites;
};
