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
#include "StageManager.h"
#include "TextureManager.h"
#include "TransformComponent.h"
#include "VelocityComponent.h"
#include "SpriteComponent.h"
#include "PathComponent.h"
#include "CaracComponent.h"
#include "AttackTowerComponent.h"
#include "CreepComponent.h"
#include "RenderSystem.h"
#include "MovementSystem.h"
#include "AIFollowPathSystem.h"
#include "AITowerSystem.h"
#include "Camera.h"
#include "main.h"

int main(int argc, char *argv[])
{
	const GLuint width(40 * 10);
	const GLuint height(40 * 20);

	sf::ContextSettings settings;
	settings.depthBits = 0;
	settings.stencilBits = 0;
	settings.antialiasingLevel = 0;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	sf::Window window(sf::VideoMode(width, height), "Tower Defense", sf::Style::Default, settings);

	if (glewInit() != GLEW_OK) {
		std::cerr << "Glew init error!" << std::endl;
		return EXIT_FAILURE;
	}

	Camera camera(static_cast<GLfloat>(width), static_cast<GLfloat>(height));

	TextureManager textureManager;
	StageManager stageManager(textureManager);
	Stage stage1 = stageManager.create("maps/map1.td");

	// optimisation tilemap avoir un seul VAO ?

	EntityManager entityManager;

	RenderSystem renderSystem(entityManager, stage1, camera);
	MovementSystem movementSystem(entityManager);
	AIFollowPathSystem aiFollowPathSystem(entityManager, stage1);
	AITowerSystem aiTowerSystem(entityManager);

	// Creep
	Entity entityCreep = entityManager.createEntity();
	{
		auto transform = std::make_unique<TransformComponent>();
		entityManager.addComponent(entityCreep, std::move(transform));
	}
	{
		auto velocity = std::make_unique<VelocityComponent>(glm::vec2(0, 0), 100.0f);
		entityManager.addComponent(entityCreep, std::move(velocity));
	}
	{
		auto sprite = std::make_unique<SpriteComponent>(glm::vec2(40, 40), glm::vec2(0, 0), textureManager.getTexture("textures/debug.png"));
		entityManager.addComponent(entityCreep, std::move(sprite));
	}
	{
		auto path = std::make_unique<PathComponent>();
		entityManager.addComponent(entityCreep, std::move(path));
	}
	{
		auto carac = std::make_unique<CaracComponent>(100, 0.0f, 0.0f, 0.0f);
		entityManager.addComponent(entityCreep, std::move(carac));
	}
	{
		auto creep = std::make_unique<CreepComponent>();
		entityManager.addComponent(entityCreep, std::move(creep));
	}
	renderSystem.registerEntity(entityCreep);
	movementSystem.registerEntity(entityCreep);
	aiFollowPathSystem.registerEntity(entityCreep);

	// Tower
	{
		Entity entity = entityManager.createEntity();
		{
			auto transform = std::make_unique<TransformComponent>(glm::vec3(120.0f, 600.0f, 0.0f));
			entityManager.addComponent(entity, std::move(transform));
		}
		{
			auto sprite = std::make_unique<SpriteComponent>(glm::vec2(40, 40), glm::vec2(0, 0), textureManager.getTexture("textures/debug.png"));
			entityManager.addComponent(entity, std::move(sprite));
		}
		{
			auto carac = std::make_unique<CaracComponent>(0, 0.0f, 20.0f, 10.0f);
			entityManager.addComponent(entity, std::move(carac));
		}
		{
			auto attackTower = std::make_unique<AttackTowerComponent>(sf::seconds(1.0f), 10, 100.0f);
			entityManager.addComponent(entity, std::move(attackTower));
		}
		renderSystem.registerEntity(entity);
		aiTowerSystem.registerEntity(entity);
		aiTowerSystem.addCreep(entityCreep);
	}
	

	sf::Clock clock;
	const float FPS(1.0f / 60.0f);

	auto running(true);
	while (running)
	{
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				running = false;
			}
			else if (event.type == sf::Event::Resized) {
				// on ajuste le viewport lorsque la fenêtre est redimensionnée
				glViewport(0, 0, event.size.width, event.size.height);
				camera.setWidth((GLfloat)event.size.width);
				camera.setHeight((GLfloat)event.size.height);
			}
			else if (event.type == sf::Event::LostFocus) {
			}
			else if (event.type == sf::Event::GainedFocus) {
			}
			else if (event.type == sf::Event::KeyReleased) {
				if (event.key.code == sf::Keyboard::Escape) {
					running = false;
				}
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					auto mouseInWorld = camera.screenToWorld(glm::vec2(event.mouseButton.x, event.mouseButton.y));
					std::cout << "mouse : " << mouseInWorld.x << "; " << mouseInWorld.y << std::endl;
				}
			}
		}

		// update semi-fixed timestep
		auto elapsed = clock.restart().asSeconds();
		while (elapsed > 0.0f)
		{
			float deltaTime = glm::min(elapsed, FPS);
			//camera.move(glm::vec3(0.0f, 3.0f, 0.0f) * elapsed);

			// system updates
			aiFollowPathSystem.update(deltaTime);
			movementSystem.update(deltaTime);
			aiTowerSystem.update(deltaTime);

			elapsed -= deltaTime;
		}

		// render
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		renderSystem.update();

		window.display();
	}

	entityManager.clean();

	//system("pause");
	return EXIT_SUCCESS;
}
