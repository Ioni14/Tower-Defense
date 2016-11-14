#pragma once

#include <memory>
#include <map>
#include <vector>
#include <assert.h>
#include "Entity.h"
#include "Component.h"
#include "AttackTowerComponent.h"
#include "CaracComponent.h"
#include "CreepComponent.h"
#include "PathComponent.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"

#include <iostream>

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	auto createEntity() {
		Entity entity(m_nextEntity++);
		std::cout << "[Entity] creation : #" << entity << std::endl;
		//m_entities[entity] = ComponentVector();
		return entity;
	}
	/*
	void addComponent(Entity const& entity, std::unique_ptr<Component>&& component) {

		// TODO : use vector for each Component
		// std::vector<std::unique_ptr<CaracComponent>> caracComponents;
		// std::vector<std::unique_ptr<SpriteComponent>> spriteComponents;

		// carac = std::make_unique<CaracComponent>();
		// caracComponents.insert(caracComponents.cbegin() + (entity - 1), std::move(carac)); // -1 because entity #0 does not exist

		// TODO : checks if has already this type of component
		m_entities[entity].push_back(std::move(component));
	}
	*/
	void removeComponent(Entity const& entity, Component::Type type) {
		std::runtime_error("not yet implemented");
		// TODO : foreach components of entity : if (type == comp->getType()) : remove; return;
	}
	
	/*
	ComponentVector& getComponents(Entity const& entity) {
		return m_entities[entity];
	}
	*/
	/*
	Component* getComponent(Entity const& entity, Component::Type type) {
		auto& compos = m_entities[entity];
		for (auto& compo : compos) {
			if (compo->getType() == type) {
				return compo.get();
			}
		}
		return nullptr;
	}
	*/
	/*
	template<typename C>
	C* getComponent<C>(Entity entity) {
		static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component");
		
	}
	*/
	auto getAttackTowerComponent(Entity entity) {
		auto& compo = attackTowerComponents[entity - 1];
		return compo.get();
	}
	auto getCaracComponent(Entity entity) {
		auto& compo = caracComponents[entity - 1];
		return compo.get();
	}
	auto getCreepComponent(Entity entity) {
		auto& compo = creepComponents[entity - 1];
		return compo.get();
	}
	auto getPathComponent(Entity entity) {
		auto& compo = pathComponents[entity - 1];
		return compo.get();
	}
	auto getSpriteComponent(Entity entity) {
		auto& compo = spriteComponents[entity - 1];
		return compo.get();
	}
	auto getTransformComponent(Entity entity) {
		auto& compo = transformComponents[entity - 1];
		return compo.get();
	}
	auto getVelocityComponent(Entity entity) {
		auto& compo = velocityComponents[entity - 1];
		return compo.get();
	}


	void clean() {
		/*
		for (auto& it = m_entities.begin(); it != m_entities.end();) {
			for (auto& compoIt = it->second.begin(); compoIt != it->second.end();) {
				(*compoIt)->destroy();
				compoIt = it->second.erase(compoIt);
			}
			it = m_entities.erase(it);
		}
		*/
		for (auto& compoIt = attackTowerComponents.begin(); compoIt != attackTowerComponents.end();) {
			(*compoIt)->destroy();
			compoIt = attackTowerComponents.erase(compoIt);
		}
		for (auto& compoIt = caracComponents.begin(); compoIt != caracComponents.end();) {
			(*compoIt)->destroy();
			compoIt = caracComponents.erase(compoIt);
		}
		for (auto& compoIt = creepComponents.begin(); compoIt != creepComponents.end();) {
			(*compoIt)->destroy();
			compoIt = creepComponents.erase(compoIt);
		}
		for (auto& compoIt = pathComponents.begin(); compoIt != pathComponents.end();) {
			(*compoIt)->destroy();
			compoIt = pathComponents.erase(compoIt);
		}
		for (auto& compoIt = spriteComponents.begin(); compoIt != spriteComponents.end();) {
			(*compoIt)->destroy();
			compoIt = spriteComponents.erase(compoIt);
		}
		for (auto& compoIt = transformComponents.begin(); compoIt != transformComponents.end();) {
			(*compoIt)->destroy();
			compoIt = transformComponents.erase(compoIt);
		}
		for (auto& compoIt = velocityComponents.begin(); compoIt != velocityComponents.end();) {
			(*compoIt)->destroy();
			compoIt = velocityComponents.erase(compoIt);
		}
	}


	/*
	template<typename C>
	void addComp(Entity entity, std::unique_ptr<C>&& component) {
		static_assert(std::is_base_of<Component, C>::value, "C must inherit from Component");
	}
	*/

	void addAttackTowerComponent(Entity entity, AttackTowerComponent::Ptr&& compo) {
		attackTowerComponents.insert(attackTowerComponents.cbegin() + (entity - 1), std::move(compo));
	}
	void addCaracComponent(Entity entity, CaracComponent::Ptr&& compo) {
		caracComponents.insert(caracComponents.cbegin() + (entity - 1), std::move(compo));
	}
	void addCreepComponent(Entity entity, CreepComponent::Ptr&& compo) {
		creepComponents.insert(creepComponents.cbegin() + (entity - 1), std::move(compo));
	}
	void addPathComponent(Entity entity, PathComponent::Ptr&& compo) {
		pathComponents.insert(pathComponents.cbegin() + (entity - 1), std::move(compo));
	}
	void addSpriteComponent(Entity entity, SpriteComponent::Ptr&& compo) {
		spriteComponents.insert(spriteComponents.cbegin() + (entity - 1), std::move(compo));
	}
	void addTransformComponent(Entity entity, TransformComponent::Ptr&& compo) {
		transformComponents.insert(transformComponents.cbegin() + (entity - 1), std::move(compo));
	}
	void addVelocityComponent(Entity entity, VelocityComponent::Ptr&& compo) {
		velocityComponents.insert(velocityComponents.cbegin() + (entity - 1), std::move(compo));
	}

private:
	//std::map<Entity, ComponentVector> m_entities;
	std::vector<AttackTowerComponent::Ptr> attackTowerComponents;
	std::vector<CaracComponent::Ptr> caracComponents;
	std::vector<CreepComponent::Ptr> creepComponents;
	std::vector<PathComponent::Ptr> pathComponents;
	std::vector<SpriteComponent::Ptr> spriteComponents;
	std::vector<TransformComponent::Ptr> transformComponents;
	std::vector<VelocityComponent::Ptr> velocityComponents;

	Entity m_nextEntity;
};
