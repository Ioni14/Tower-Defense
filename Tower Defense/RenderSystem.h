#pragma once

#include "System.h"
#include "Shader.h"
#include "Camera.h"

class RenderSystem :
	public System
{
public:
	explicit RenderSystem(EntityManager& entityManager, Camera& camera);
	virtual ~RenderSystem();

	virtual void update(float elapsed);
	virtual bool isGranted(Entity const& entity) const;

private:
	Camera& m_camera;
	Shader m_basicShader;
};
