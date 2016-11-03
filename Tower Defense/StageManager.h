#pragma once

#include <string>
#include "Stage.h"

class StageManager
{
public:
	explicit StageManager(TextureManager& textureManager);
	~StageManager();

	Stage create(std::string const& filepath);

private:
	TextureManager& m_textureManager;
};
