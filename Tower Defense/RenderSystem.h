#pragma once

#include "System.h"
#include "Shader.h"

class RenderSystem :
	public System
{
public:
	explicit RenderSystem(EntityManager& entityManager);
	virtual ~RenderSystem();

	virtual void update(float elapsed);
	virtual bool isGranted(Entity const& entity) const;

private:
	Shader m_basicShader;
};
