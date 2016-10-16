#include "RenderSystem.h"

#include <iostream>
#include "TransformComponent.h"
#include "SpriteComponent.h"

RenderSystem::RenderSystem(EntityManager & entityManager) :
	System(entityManager)
{
	m_basicShader.addFile("shaders/basic.vert", Shader::Type::VERTEX);
	m_basicShader.addFile("shaders/basic.frag", Shader::Type::FRAGMENT);
	m_basicShader.create();
}

RenderSystem::~RenderSystem()
{
	m_basicShader.destroy();
}

void RenderSystem::update(float elapsed)
{
	// camera (viewMatrix projectionMatrix)


	m_basicShader.use();

	for (auto const& entity : m_entites) {
		TransformComponent* transform = dynamic_cast<TransformComponent*>(m_entityManager.getComponent(entity, Component::Type::TRANSFORM));
		SpriteComponent* sprite = dynamic_cast<SpriteComponent*>(m_entityManager.getComponent(entity, Component::Type::SPRITE));

		m_basicShader.sendMatrix4x4("transform", transform->getMatrix());
		sprite->draw();
	}

	m_basicShader.unuse();
}

bool RenderSystem::isGranted(Entity const & entity) const
{
	int cc(0);
	auto& compos = m_entityManager.getComponents(entity);
	for (auto const& compo : compos) {
		switch (compo->getType()) {
		case Component::Type::TRANSFORM:
		case Component::Type::SPRITE:
			cc++;
		}
	}
	return cc == 2;
}
