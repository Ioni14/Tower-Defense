#pragma once

#include "Component.h"

#include <SFML/System/Time.hpp>
#include <GL/glew.h>
#include "Entity.h"

class AttackTowerComponent :
	public Component
{
public:
	using Ptr = std::unique_ptr<AttackTowerComponent>;

	AttackTowerComponent(sf::Time const& cooldown, GLuint damage, GLfloat range);
	virtual ~AttackTowerComponent();

	virtual Type getType() const {
		return Type::ATTACK_TOWER;
	}

	auto getDamage() const {
		return m_damage;
	}

	auto getRange() const {
		return m_range;
	}

	const auto getTarget() const {
		return m_target;
	}

	bool hasTarget() const {
		return m_target != nullptr;
	}

	void setTarget(Entity const* entity) {
		m_target = entity;
	}

	const auto& getActualCooldown() const {
		return m_cooldown;
	}

	void stepCooldown(float elapsed) {
		if (!canAttack()) {
			m_cooldown -= sf::seconds(elapsed);
			if (m_cooldown < sf::Time::Zero) {
				m_cooldown = sf::Time::Zero;
			}
		}
	}

	void resetCooldown() {
		m_cooldown = m_cooldownFull;
	}

	bool canAttack() const {
		return m_cooldown <= sf::Time::Zero;
	}

private:
	const sf::Time m_cooldownFull; /**< total cooldown of the attack*/
	sf::Time m_cooldown; /**< actual cooldown*/
	GLuint m_damage; /**< raw damage*/
	GLfloat m_percentCritical; /**< percent of chances for critical attacks*/
	GLfloat m_range; /**< distance for targeting/attacking creeps*/
	Entity const* m_target; /**< actuel entity target (targetable && attackable) */
};
