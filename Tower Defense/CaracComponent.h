#pragma once

#include "Component.h"
#include <GL/glew.h>

class CaracComponent :
	public Component
{
public:
	using Ptr = std::unique_ptr<CaracComponent>;

	CaracComponent(GLuint health, GLfloat defense, GLfloat critical, GLfloat haste);
	virtual ~CaracComponent();

	virtual Type getType() const {
		return Type::CARAC;
	}

	auto getHealth() const {
		return m_health;
	}

	void gainHealth(GLuint amount) {
		m_health += amount;
		if (m_health > m_healthMax) {
			m_health = m_healthMax;
		}
	}

	void dropHealth(GLuint amount) {
		if (m_health < amount) {
			m_health = 0;
			return;
		}
		m_health -= amount;
	}

	bool isDead() const {
		return m_health == 0;
	}

private:
	GLuint m_healthMax; /**< amount of health points (0 = dead)*/
	GLuint m_health; /**< amount of actual health*/

	GLfloat m_defense; /**< percentage of reduce critical*/
	GLfloat m_critical; /**< percentage of chances for x2 damages*/
	GLfloat m_haste; /**< percentage of reduce cooldown attacks*/
};
