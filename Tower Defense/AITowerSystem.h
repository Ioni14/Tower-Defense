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

	void addCreep(Entity creep) {
		m_creeps.push_back(creep);
	}

	void removeCreep(Entity creep) {
		for (auto it = m_creeps.cbegin(); it != m_creeps.cend();) {
			if (*it == creep) {
				m_creeps.erase(it);
			}
			else {
				it++;
			}
		}
	}

private:
	// TODO : observer/observed pattern for spawning/despawning of creep for maintaining the list
	std::vector<Entity> m_creeps; /**< all creeps can be attacked by towers */
};
