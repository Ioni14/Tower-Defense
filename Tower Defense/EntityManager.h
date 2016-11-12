#pragma once

#include <memory>
#include <map>
#include <vector>
#include <assert.h>
#include "Entity.h"
#include "Component.h"

class EntityManager
{
public:
	typedef std::unique_ptr<Component> PtrComponent;
	typedef std::vector<PtrComponent> ComponentVector;

	EntityManager();
	~EntityManager();

	auto createEntity() {
		Entity entity(m_nextEntity++);
		m_entities[entity] = ComponentVector();
		return entity;
	}
	void addComponent(Entity const& entity, std::unique_ptr<Component>&& component) {
		// TODO : checks if has already this type of component
		m_entities[entity].push_back(std::move(component));
	}
	void removeComponent(Entity const& entity, Component::Type type) {
		std::runtime_error("not yet implemented");
		// TODO : foreach components of entity : if (type == comp->getType()) : remove; return;
	}

	ComponentVector& getComponents(Entity const& entity) {
		return m_entities[entity];
	}
	Component* getComponent(Entity const& entity, Component::Type type) {
		for (auto& compo : m_entities[entity]) {
			if (compo->getType() == type) {
				return compo.get();
			}
		}
		return nullptr;
	}

	void clean() {
		for (auto& it = m_entities.begin(); it != m_entities.end();) {
			for (auto& compoIt = it->second.begin(); compoIt != it->second.end();) {
				(*compoIt)->destroy();
				compoIt = it->second.erase(compoIt);
			}
			it = m_entities.erase(it);
		}
	}

private:
	std::map<Entity, ComponentVector> m_entities;
	Entity m_nextEntity;
};
