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

	Entity createEntity() {
		Entity entity(m_nextEntity++);
		m_entities[entity] = ComponentVector();
		return entity;
	}
	void addComponent(Entity const& entity, std::unique_ptr<Component> component) {
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

private:
	std::map<Entity, ComponentVector> m_entities;
	Entity m_nextEntity;
};
