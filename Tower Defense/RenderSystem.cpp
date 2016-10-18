#include "RenderSystem.h"

#include <iostream>
#include "TransformComponent.h"
#include "SpriteComponent.h"

RenderSystem::RenderSystem(EntityManager & entityManager, Camera& camera) :
	System(entityManager),
	m_camera(camera),
	m_basicShader()
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
	glm::mat4 const& view = m_camera.getViewMatrix();
	glm::mat4 const& projection = m_camera.getProjectionMatrix();

	m_basicShader.use();
	m_basicShader.sendTexture("tex", 0);

	for (auto const& entity : m_entites) {
		TransformComponent* transform = dynamic_cast<TransformComponent*>(m_entityManager.getComponent(entity, Component::Type::TRANSFORM));
		SpriteComponent* sprite = dynamic_cast<SpriteComponent*>(m_entityManager.getComponent(entity, Component::Type::SPRITE));

		m_basicShader.sendMatrix4x4("transform", transform->getMatrix());
		m_basicShader.sendMatrix4x4("view", view);
		m_basicShader.sendMatrix4x4("projection", projection);

		// TODO : optimisation si plusieurs entités utilisent la même texture (tri ?)
		sprite->getTexture().use(); // texture0

		sprite->draw();

		sprite->getTexture().unuse();
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
