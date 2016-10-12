#include "MovementSystem.h"

#include <iostream>
#include "TransformComponent.h"
#include "VelocityComponent.h"

MovementSystem::MovementSystem(EntityManager & entityManager) :
	System(entityManager)
{
}

MovementSystem::~MovementSystem()
{
}

void MovementSystem::update(float elapsed)
{
	for (auto const& entity : m_entites) {
		TransformComponent* transform = dynamic_cast<TransformComponent*>(m_entityManager.getComponent(entity, Component::Type::TRANSFORM));
		VelocityComponent* velocity = dynamic_cast<VelocityComponent*>(m_entityManager.getComponent(entity, Component::Type::VELOCITY));

		transform->move(glm::vec3(velocity->getVelocity() * elapsed, 0.0f));
	}
}

bool MovementSystem::isGranted(Entity const& entity) const
{
	int cc(0);
	auto& compos = m_entityManager.getComponents(entity);
	for (auto const& compo : compos) {
		switch (compo->getType()) {
			case Component::Type::TRANSFORM:
			case Component::Type::VELOCITY:
				cc++;
		}
	}
	return cc == 2;
}
