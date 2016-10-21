#include "StageManager.h"

#include <sstream>
#include <fstream>
#include <iostream>

StageManager::StageManager()
{
}


StageManager::~StageManager()
{
}

Stage StageManager::create(std::string const& filepath)
{
	Stage stage;

	std::ifstream file(filepath);

	if (file.fail()) {
		std::cerr << "could not open file " << filepath << std::endl;
		return stage;
	}
	std::string line;
	while (!file.fail())
	{
		std::getline(file, line);
		if (line.empty()) {
			continue;
		}

		std::vector<std::string> items;
		{
			std::stringstream ss;
			ss.str(line);
			std::string item;
			while (std::getline(ss, item, '=')) {
				items.push_back(item);
			}
		}

		if (!items.empty() && items.size() == 2) {
			// key=value
			// TODO : clean the key (trim + lowercase)
			if (items[0] == "width") {
				try {
					stage.m_size.x = std::stoi(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<width> must be an integer" << std::endl;
					return stage;
				}
				continue;
			}
			if (items[0] == "height") {
				try {
					stage.m_size.y = std::stoi(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<height> must be an integer" << std::endl;
					return stage;
				}
				continue;
			}
			if (items[0] == "tileset") {
				stage.m_tileset = Texture::createFromFile(items[1]);
				continue;
			}
			if (items[0] == "spawn_x") {
				try {
					stage.m_spawn.x = std::stoi(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<spawn_x> must be an integer" << std::endl;
					return stage;
				}
			}
			if (items[0] == "spawn_y") {
				try {
					stage.m_spawn.y = std::stoi(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<spawn_y> must be an integer" << std::endl;
					return stage;
				}
			}
			continue;
		}

		{
			items.clear();
			std::stringstream ss;
			ss.str(line);
			std::string item;
			while (std::getline(ss, item, '/')) {
				items.push_back(item);
			}
		}

		// tiles
		if (!items.empty() && items.size() == 6 && items[0] == "t") {
			// tile/x/y/texX/texY/isBuildable
			
			// position haut gauche
			items[1]; // x
			items[2]; // y 

			// texCoords
			items[3]; // texX
			items[4]; // texY

			// plus tard.......
			items[5]; // isBuildable
			
			continue;
		}
		
	}

	std::cout << "map size : " << stage.m_size.x << "x" << stage.m_size.y << std::endl;
	std::cout << "spawn : " << stage.m_spawn.x << ";" << stage.m_spawn.y << std::endl;
	std::cout << "tilset created : " << stage.m_tileset.isCreated() << std::endl;

	return stage;
}
