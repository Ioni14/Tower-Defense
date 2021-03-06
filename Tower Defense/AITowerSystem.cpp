#include "AITowerSystem.h"

#include <iostream>
#include "TransformComponent.h"
#include "AttackTowerComponent.h"
#include "CaracComponent.h"
#include "CreepComponent.h"

AITowerSystem::AITowerSystem(EntityManager & entityManager) :
	System(entityManager),
	m_creeps()
{
}

AITowerSystem::~AITowerSystem()
{
}

void AITowerSystem::update(float elapsed)
{
	for (auto const& entity : m_entities) {
		auto transform = m_entityManager.getTransformComponent(entity);
		auto attackTower = m_entityManager.getAttackTowerComponent(entity);
		//auto transform = dynamic_cast<TransformComponent*>(m_entityManager.getComponent(entity, Component::Type::TRANSFORM));
		//auto attackTower = dynamic_cast<AttackTowerComponent*>(m_entityManager.getComponent(entity, Component::Type::ATTACK_TOWER));

		if (!attackTower->canAttack()) {
			// in cooldown => cannot attack
			attackTower->stepCooldown(elapsed);
			continue;
		}

		// Has a target
		if (attackTower->hasTarget()) {
			// checks if target still in range
			auto target = *attackTower->getTarget();

			auto transformFocus = m_entityManager.getTransformComponent(target);
			auto caracFocus = m_entityManager.getCaracComponent(target);
			//auto transformFocus = dynamic_cast<TransformComponent*>(m_entityManager.getComponent(target, Component::Type::TRANSFORM));
			//auto caracFocus = dynamic_cast<CaracComponent*>(m_entityManager.getComponent(target, Component::Type::CARAC));

			if (transformFocus == nullptr || caracFocus == nullptr) {
				// maybe focus does not exist anymore
				attackTower->setTarget(nullptr);
			}
			else {
				if (caracFocus->isDead()) {
					attackTower->setTarget(nullptr);
					std::cout << "Focus lost" << std::endl;
				}
				else {
					auto distTowerToFocus = glm::distance(transformFocus->getPosition(), transform->getPosition());

					std::cout << "Distance to #" << target << " : " << distTowerToFocus << std::endl;

					if (distTowerToFocus > attackTower->getRange()) {
						// too far away
						attackTower->setTarget(nullptr);
						std::cout << "Focus lost" << std::endl;
					}
				}
			}

		}

		// Not already target or lost it : try to get new
		if (!attackTower->hasTarget()) {
			// target the closest

			auto distanceMin(0.0f);
			Entity const* entityMin(nullptr);
			for (auto const& entityTarget : m_creeps) {

				auto const* const transformTarget = m_entityManager.getTransformComponent(entityTarget);
				auto const* const caracTarget = m_entityManager.getCaracComponent(entityTarget);
				auto const* const creepTarget = m_entityManager.getCreepComponent(entityTarget);
				//const auto transformTarget = dynamic_cast<TransformComponent*>(m_entityManager.getComponent(entityTarget, Component::Type::TRANSFORM));
				//const auto caracTarget = dynamic_cast<CaracComponent*>(m_entityManager.getComponent(entityTarget, Component::Type::CARAC));
				//const auto creepTarget = dynamic_cast<CreepComponent*>(m_entityManager.getComponent(entityTarget, Component::Type::CREEP));

				if (creepTarget == nullptr || transformTarget == nullptr || caracTarget == nullptr) {
					// not attackable
					continue;
				}
				
				if (caracTarget->isDead()) {
					continue;
				}

				auto distTowerToTarget = glm::distance(transformTarget->getPosition(), transform->getPosition());

				if (distTowerToTarget > attackTower->getRange()) {
					// too far away
					continue;
				}

				std::cout << "Search new focus... Distance to #" << entityTarget << " : " << distTowerToTarget << std::endl;

				if (entityMin == nullptr || distTowerToTarget < distanceMin) {
					distanceMin = distTowerToTarget;
					entityMin = &entityTarget;
				}

			}

			attackTower->setTarget(entityMin);
		}

		// No target found : no attack
		if (!attackTower->hasTarget()) {
			continue;
		}

		// finally attack the target
		attackTower->resetCooldown();

		auto caracFocus = m_entityManager.getCaracComponent(*attackTower->getTarget());
		//auto caracFocus = dynamic_cast<CaracComponent*>(m_entityManager.getComponent(*attackTower->getTarget(), Component::Type::CARAC));
		caracFocus->dropHealth(attackTower->getDamage());

		std::cout << "la tour #" << entity << " fait " << attackTower->getDamage() << " degats." << std::endl;
		std::cout << "l'entite #" << *attackTower->getTarget() << " n'a plus que " << caracFocus->getHealth() << " PV." << std::endl;

		if (caracFocus->isDead()) {
			std::cout << "l'entite #" << *attackTower->getTarget() << " est morte." << std::endl;
			attackTower->setTarget(nullptr);
		}

		// create the attack entity with all damage bonus/malus
		// example : raw damage of 100 + BUFF physical damage of 50% = 100 * 1.5 = 150 + DEBUFF critical damage 10%
		// critical attribute base : 30% - debuff = 30% - 10% = 20%
		// => attack entity get 150 damage and 20% crit
		// 20% chances for 150 * 2 = 300 damages (crit)
		// 80% chances for 150 * 1 = 150 damages (normal)
		// resolution : per target compute buff and debuff and attributes
		// example : target with BUFF reduction damage of 25% + attribute armor of 70% + attribute defense of 10%
		// => 150 damages * 0.75 * 0.30 = 33.75. 20% crit - 10% def = 10% crit. 
		// 10% chances for 33.75 * 2 = ceil(67.5) = 68
		// 90% chances for 33.75 * 1 = ceil(33.75) = 34
		
		// attributes : 
		// health (0 = dead) 
		// damage (physical, fire, frost, nature, shadow, light) in AttackComponent
		// critical (chances to do x2 damages) 
		// defense (reduce incoming critical) 
		// haste (up frequency of attacks)
	}
}

bool AITowerSystem::isGranted(Entity const & entity) const
{
	auto attackTower = m_entityManager.getAttackTowerComponent(entity);
	auto transform = m_entityManager.getTransformComponent(entity);

	return transform != nullptr && attackTower != nullptr;
	
	/*
	auto cc(0);
	auto& compos = m_entityManager.getComponents(entity);
	for (auto const& compo : compos) {
		switch (compo->getType()) {
		case Component::Type::ATTACK_TOWER:
		case Component::Type::TRANSFORM:
			cc++;
		}
	}
	return cc == 2;
	*/
}
