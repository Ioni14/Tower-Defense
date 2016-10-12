#include "System.h"

System::System(EntityManager & entityManager) :
	m_entityManager(entityManager),
	m_entites()
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
	for (auto const& e : m_entites) {
		if (e == entity) {
			return;
		}
	}
	m_entites.push_back(entity);
}

void System::unregisterEntity(Entity entity)
{
	for (auto& it = m_entites.begin(); it != m_entites.end(); it++) {
		if (*it == entity) {
			m_entites.erase(it);
			return;
		}
	}
}
