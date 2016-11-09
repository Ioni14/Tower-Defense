#include "AttackTowerComponent.h"

AttackTowerComponent::AttackTowerComponent(sf::Time const & cooldown, GLuint damage, GLfloat range) :
	m_cooldownFull(cooldown),
	m_cooldown(cooldown),
	m_damage(damage),
	m_range(range),
	m_target(nullptr)
{
}

AttackTowerComponent::~AttackTowerComponent()
{
}
