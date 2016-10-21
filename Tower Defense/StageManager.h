#pragma once

#include <string>
#include "Stage.h"

class StageManager
{
public:
	StageManager();
	~StageManager();

	Stage create(std::string const& filepath);
};
