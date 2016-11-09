#pragma once

#include "Component.h"

#include <glm/matrix.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>

class PathComponent :
	public Component
{
public:
	typedef std::unique_ptr<PathComponent> Ptr;

	PathComponent();
	virtual ~PathComponent();

	virtual Type getType() const {
		return Type::PATH;
	}

	auto getIndexNextCheckpoint() const {
		return m_indexNextCheckpoint;
	}
	void setIndexNextCheckpoint(int index) {
		m_indexNextCheckpoint = index;
	}
	void incrementCheckpoint() {
		m_indexNextCheckpoint++;
	}

	auto hasSpawned() const {
		return m_spawned;
	}

	/**
	 * change "spawn" flag state and initialize next checkpoint
	 */
	void spawn() {
		if (m_spawned) {
			return;
		}
		m_spawned = true;
		m_indexNextCheckpoint = 0;
	}

private:
	bool m_spawned; /**< true if entity has spawned*/
	size_t m_indexNextCheckpoint; /**< the n-th checkpoint where entity must go*/
};
