#pragma once

#include "System.h"
#include "Shader.h"
#include "Camera.h"
#include "Stage.h"

class RenderSystem :
	public System
{
public:
	explicit RenderSystem(EntityManager& entityManager, Stage const& stage, Camera& camera);
	virtual ~RenderSystem();

	virtual void update(float elapsed);
	void update();
	virtual bool isGranted(Entity const& entity) const;

private:
	Camera& m_camera;
	Shader m_basicShader;
	Shader m_tilemapShader;

	Stage m_stage;
};
