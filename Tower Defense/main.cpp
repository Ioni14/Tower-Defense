#include <cstdlib>
#include <string> 
#include <fstream> 
#include <sstream>
#include <iostream> 
#include <cmath>

#include <SFML/Graphics.hpp>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "Shader.h"
#include "EntityManager.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"
#include "SpriteComponent.h"
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "Camera.h"

/*
TextureManager
ShaderManager

SpriteComponent : shape + texture(opt)
*/

int main(int argc, char *argv[])
{
	sf::ContextSettings settings;
	settings.depthBits = 0;
	settings.stencilBits = 0;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	sf::Window window(sf::VideoMode(1280, 720), "OpenGL", sf::Style::Default, settings);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Glew init error!" << std::endl;
		return EXIT_FAILURE;
	}

	Camera camera(1280, 720);

	EntityManager entityManager;

	RenderSystem renderSystem(entityManager, camera);
	MovementSystem movementSystem(entityManager);

	Entity entity = entityManager.createEntity();
	auto transform = std::make_unique<TransformComponent>();
	transform->setTranslation(glm::vec3(0, 256, 0.0f));
	transform->setRotation(0);
	transform->setScale(glm::vec2(1, 1));
	entityManager.addComponent(entity, std::move(transform));
	transform = nullptr;
	auto velocity = std::make_unique<VelocityComponent>(glm::vec2(0, 0), glm::vec2(150.0f, 70.0f));
	entityManager.addComponent(entity, std::move(velocity));
	velocity = nullptr;
	auto sprite = std::make_unique<SpriteComponent>(256.0f);
	entityManager.addComponent(entity, std::move(sprite));
	sprite = nullptr;

	renderSystem.registerEntity(entity);
	movementSystem.registerEntity(entity);

	sf::Clock clock;

	bool running = true;
	while (running)
	{
		sf::Time elapsed = clock.restart();

		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed) {
				running = false;
			} else if (event.type == sf::Event::Resized) {
				// on ajuste le viewport lorsque la fenêtre est redimensionnée
				glViewport(0, 0, event.size.width, event.size.height);
				camera.setWidth(event.size.width);
				camera.setHeight(event.size.height);
			}

		}

		// update
		movementSystem.update(elapsed.asSeconds());

		// effacement les tampons de couleur/profondeur
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderSystem.update(elapsed.asSeconds());

		window.display();
	}

	return EXIT_SUCCESS;
}
