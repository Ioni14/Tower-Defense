#include "RenderSystem.h"

#include <iostream>
#include "TransformComponent.h"
#include "SpriteComponent.h"

RenderSystem::RenderSystem(EntityManager & entityManager, Stage const& stage, Camera& camera) :
	System(entityManager),
	m_camera(camera),
	m_basicShader(),
	m_stage(stage)
{
	m_basicShader.addFile("shaders/basic.vert", Shader::Type::VERTEX);
	m_basicShader.addFile("shaders/basic.frag", Shader::Type::FRAGMENT);
	m_basicShader.create();

	m_tilemapShader.addFile("shaders/tilemap.vert", Shader::Type::VERTEX);
	m_tilemapShader.addFile("shaders/tilemap.frag", Shader::Type::FRAGMENT);
	m_tilemapShader.create();
}

RenderSystem::~RenderSystem()
{
	m_basicShader.destroy();
	m_tilemapShader.destroy();
}

void RenderSystem::update()
{
	update(0.0f);
}

void RenderSystem::update(float elapsed)
{
	glm::mat4 const& view = m_camera.getViewMatrix();
	glm::mat4 const& projection = m_camera.getProjectionMatrix();

	m_tilemapShader.use();
	m_tilemapShader.sendTexture("tex", 0);
	m_tilemapShader.sendMatrix4x4("projection", projection);

	m_stage.getTileset().use(0);

	auto& tiles = m_stage.getTiles();
	for (auto& tile : tiles) {
		auto& transform = tile.getTransform();
		auto& sprite = tile.getSprite();

		m_tilemapShader.sendMatrix4x4("model_view", view * transform.getMatrix());

		sprite.draw();
	}
	m_stage.getTileset().unuse(0);
	m_tilemapShader.unuse();

	m_basicShader.use();
	m_basicShader.sendTexture("tex", 0);
	m_basicShader.sendMatrix4x4("view", view);
	m_basicShader.sendMatrix4x4("projection", projection);

	for (auto const& entity : m_entities) {
		auto transform = dynamic_cast<TransformComponent*>(m_entityManager.getComponent(entity, Component::Type::TRANSFORM));
		auto sprite = dynamic_cast<SpriteComponent*>(m_entityManager.getComponent(entity, Component::Type::SPRITE));

		m_basicShader.sendMatrix4x4("transform", transform->getMatrix());

		// TODO : optimisation si plusieurs entités utilisent la même texture (tri ?)
		sprite->getTexture().use(0);
		sprite->draw();
		sprite->getTexture().unuse(0);
	}

	m_basicShader.unuse();
}

bool RenderSystem::isGranted(Entity const & entity) const
{
	auto cc(0);
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
