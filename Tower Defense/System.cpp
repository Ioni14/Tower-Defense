#include "System.h"

System::System(EntityManager & entityManager) :
	m_entityManager(entityManager),
	m_entities()
{
}

System::~System()
{
}

void System::registerEntity(Entity entity)
{
	if (!isGranted(entity)) {
		return;
	}
	// checks duplicate
	for (auto const& e : m_entities) {
		if (e == entity) {
			return;
		}
	}
	m_entities.push_back(entity);
}

void System::unregisterEntity(Entity entity)
{
	for (auto& it = m_entities.begin(); it != m_entities.end();) {
		if (*it == entity) {
			it = m_entities.erase(it);
			return;
		}
		else {
			++it;
		}
	}
}
