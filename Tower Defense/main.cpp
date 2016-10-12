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
#include "RenderSystem.h"
#include "MovementSystem.h"

/*
TextureManager
ShaderManager

SpriteComponent : shape + texture(opt)

System : registerEntity() update()
RenderSystem
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

	Shader basic;
	basic.addFile("shaders/basic.vert", Shader::Type::VERTEX);
	basic.addFile("shaders/basic.frag", Shader::Type::FRAGMENT);
	basic.create();

	basic.use();
	basic.sendFloat("loopDuration", 5.0f);
	basic.unuse();

	EntityManager entityManager;

	RenderSystem renderSystem(entityManager);
	MovementSystem movementSystem(entityManager);

	Entity entity = entityManager.createEntity();
	auto transform = std::make_unique<TransformComponent>();
	transform->setTranslation(glm::vec3(1.0f, 0.5f, 0.0f));
	transform->setRotation(45.0f);
	transform->setScale(glm::vec2(1.2f, 1.2f));
	entityManager.addComponent(entity, std::move(transform));
	auto velocity = std::make_unique<VelocityComponent>(glm::vec2(0.1f, 0.0f));
	entityManager.addComponent(entity, std::move(velocity));

	renderSystem.registerEntity(entity);
	movementSystem.registerEntity(entity);

	float vertexData[] = {
		// vertices
		-0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f, -0.5f, 0.0f, 1.0f,
		 0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f,  0.5f, 0.0f, 1.0f,
		-0.5f, -1.0f, 0.0f, 1.0f,

		// colors
		1.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	unsigned short indicesData[] = {
		0, 1, 2,
		2, 3, 0,
		0, 4, 1,
	};


	GLuint vboIndices(0);
	glGenBuffers(1, &vboIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indicesData), indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	GLuint vao(0);
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

			GLuint vboVertices(0);
			glGenBuffers(1, &vboVertices);
			glBindBuffer(GL_ARRAY_BUFFER, vboVertices); // bind : on veut utiliser ce buffer
			
				glBufferData(GL_ARRAY_BUFFER, sizeof(vertexData), vertexData, GL_STATIC_DRAW);

				glEnableVertexAttribArray(0); // on active le layout location 0
				glEnableVertexAttribArray(1); // on active le layout location 1

				glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, 0); // dans le layout 0 on met les vertices (donc 4 float par vector)
				glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 0, (void*)80); // (80 = 5vert * 4floats * 4bytes) dans le layout 1 on met les colors (donc 4 float par vector)

				//glDisableVertexAttribArray(1); // on désactive le layout location 1 (pas dans le vao)
				//glDisableVertexAttribArray(0); // on désactive le layout location 0 (pas dans le vao)
				
				glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboIndices);

			glBindBuffer(GL_ARRAY_BUFFER, 0); // unbind : on n'utilise plus ce buffer

	glBindVertexArray(0);


	sf::Clock c;

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
			}

		}

		// update
		movementSystem.update(elapsed.asSeconds());
		renderSystem.update(elapsed.asSeconds());

		// effacement les tampons de couleur/profondeur
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		basic.use();
		basic.sendFloat("time", c.getElapsedTime().asSeconds());

		glBindVertexArray(vao);
			//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // wireframe mode
			glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_SHORT, 0); // indexed
		glBindVertexArray(0);

		basic.unuse();

		window.display();
	}

	basic.destroy();

	glDeleteBuffers(1, &vboIndices);
	glDeleteBuffers(1, &vboVertices);
	glDeleteVertexArrays(1, &vao);

	system("pause");
	return EXIT_SUCCESS;
}
