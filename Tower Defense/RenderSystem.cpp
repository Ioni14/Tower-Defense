#include "RenderSystem.h"

RenderSystem::RenderSystem(EntityManager & entityManager) :
	System(entityManager)
{
}

RenderSystem::~RenderSystem()
{
}

void RenderSystem::update(float elapsed)
{
	for (auto const& e : m_entites) {






	}
}

bool RenderSystem::isGranted(Entity const & entity) const
{
	return false;
}
