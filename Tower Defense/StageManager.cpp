#include "StageManager.h"

#include <sstream>
#include <fstream>
#include <iostream>
#include "TextureManager.h"

StageManager::StageManager(TextureManager& textureManager) :
	m_textureManager(textureManager)
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
			else if (items[0] == "height") {
				try {
					stage.m_size.y = std::stoi(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<height> must be an integer" << std::endl;
					return stage;
				}
				continue;
			}
			else if (items[0] == "tileset") {
				stage.m_tileset = m_textureManager.getTexture(items[1]);
				continue;
			}
			else if (items[0] == "spawn_x") {
				try {
					stage.m_spawn.x = std::stof(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<spawn_x> must be a float" << std::endl;
					return stage;
				}
			}
			else if (items[0] == "spawn_y") {
				try {
					stage.m_spawn.y = std::stof(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<spawn_y> must be a float" << std::endl;
					return stage;
				}
			}
			else if (items[0] == "finish_x") {
				try {
					stage.m_finish.x = std::stof(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<finish_x> must be a float" << std::endl;
					return stage;
				}
			}
			else if (items[0] == "finish_y") {
				try {
					stage.m_finish.y = std::stof(items[1]);
				}
				catch (std::invalid_argument e) {
					std::cerr << "<finish_y> must be a float" << std::endl;
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
			while (std::getline(ss, item, ' ')) {
				items.push_back(item);
			}
		}

		// tiles
		if (!items.empty() && items.size() == 8 && items[0] == "t") {
			// t <x> <y> <width> <height> <texCoord X> <texCoord Y> <isBuildable>

			GLfloat x(0);
			GLfloat y(0);
			GLuint width(0);
			GLuint height(0);
			GLfloat texX(0);
			GLfloat texY(0);
			GLboolean isBuildable(false);
			try {
				x = std::stof(items[1]);
				y = std::stof(items[2]);
				width = std::stoi(items[3]);
				height = std::stoi(items[4]);
				texX = std::stof(items[5]);
				texY = std::stof(items[6]);
				isBuildable = items[7] != "0";
			}
			catch (std::invalid_argument e) {
				std::cerr << "A parameter has not the correct format. line : " << line << std::endl;
				return stage;
			}

			Tile tile(glm::vec2(width, height), glm::vec2(x, y), glm::vec2(texX, texY), stage.m_tileset);
			stage.m_tiles.push_back(std::move(tile));

			continue;
		}

		// checkpoints
		if (!items.empty() && items.size() == 3 && items[0] == "cp") {
			GLfloat x(0);
			GLfloat y(0);

			try {
				x = std::stof(items[1]);
				y = std::stof(items[2]);
			}
			catch (std::invalid_argument e) {
				std::cerr << "A parameter has not the correct format. line : " << line << std::endl;
				return stage;
			}

			stage.m_checkpoints.push_back(glm::vec2(x, y));
		}
		
	}

	std::cout << "map size : " << stage.m_size.x << "x" << stage.m_size.y << std::endl;
	std::cout << "spawn : " << stage.m_spawn.x << ";" << stage.m_spawn.y << std::endl;
	std::cout << "tilset created : " << stage.m_tileset.isCreated() << std::endl;

	return stage;
}
