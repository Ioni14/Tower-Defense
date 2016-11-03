#pragma once

#include "System.h"
#include "Shader.h"
#include "Camera.h"
#include "Stage.h"

class AIFollowPathSystem :
	public System
{
public:
	explicit AIFollowPathSystem(EntityManager& entityManager, Stage const& stage);
	virtual ~AIFollowPathSystem();

	virtual void update(float elapsed);
	virtual bool isGranted(Entity const& entity) const;

private:
	Stage m_stage;
};
