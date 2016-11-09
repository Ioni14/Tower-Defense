#include "CaracComponent.h"

CaracComponent::CaracComponent(GLuint health, GLfloat defense, GLfloat critical, GLfloat haste) :
	m_healthMax(health),
	m_health(health),
	m_defense(defense),
	m_critical(critical),
	m_haste(haste)
{
}

CaracComponent::~CaracComponent()
{
}
