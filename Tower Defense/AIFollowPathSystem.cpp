#include "AIFollowPathSystem.h"

#include "TransformComponent.h"
#include "VelocityComponent.h"
#include "PathComponent.h"

AIFollowPathSystem::AIFollowPathSystem(EntityManager & entityManager, Stage const & stage) :
	System(entityManager),
	m_stage(stage)
{
}

AIFollowPathSystem::~AIFollowPathSystem()
{
}

// TODO : refonte (p'tit problème de trajectoire...)
void AIFollowPathSystem::update(float elapsed)
{
	for (auto const& entity : m_entities) {
		TransformComponent* transform = dynamic_cast<TransformComponent*>(m_entityManager.getComponent(entity, Component::Type::TRANSFORM));
		VelocityComponent* velocity = dynamic_cast<VelocityComponent*>(m_entityManager.getComponent(entity, Component::Type::VELOCITY));
		PathComponent* path = dynamic_cast<PathComponent*>(m_entityManager.getComponent(entity, Component::Type::PATH));
















		// If entity has not spawned [TODO : when the time has come (create/activate the entity when the time has come)] : we spawn it on the spawn position
		if (!path->hasSpawned()) {
			path->spawn();
			transform->setTranslation(glm::vec3(m_stage.getSpawn(), 0));
		}

		// Calculate the entity direction (toward of the next checkpoint)
		int indexNextCheckpoint = path->getIndexNextCheckpoint();
		glm::vec2 nextCP;
		if (indexNextCheckpoint < m_stage.getCheckpoints().size()) {
			nextCP = m_stage.getCheckpoints()[indexNextCheckpoint];
		}
		else {
			nextCP = m_stage.getFinish();
		}
		
		// TODO : if nextCP == transform->getPosition() : divide by 0 error
		glm::vec2 posToCP = glm::normalize(nextCP - glm::vec2(transform->getPosition())); // direction of entity to next checkpoint normalized

		// Compute into one-frame velocity (from direction normalized with speed)
		glm::vec2 vel = posToCP * velocity->getSpeed() * elapsed;

		// Compute the remaining distance
		float distancePosToCP = glm::distance(nextCP, glm::vec2(transform->getPosition())); // the distance between entity and CP

		float distanceRemaining = glm::length(vel); // the one-frame distance travelled by entity toward the CP
		float distanceActualToNext = distancePosToCP; // the distance between checkpoints

		bool pathFinished(false);
		glm::vec2 posActualCP = transform->getPosition();
		while (distanceRemaining > distanceActualToNext) {
			distanceRemaining -= distanceActualToNext;

			if (indexNextCheckpoint < m_stage.getCheckpoints().size()) {
				indexNextCheckpoint++;
			}
			else {
				pathFinished = true;
				break;
			}

			posActualCP = nextCP;
			if (indexNextCheckpoint < m_stage.getCheckpoints().size()) {
				nextCP = m_stage.getCheckpoints()[indexNextCheckpoint];
			}
			else {
				nextCP = m_stage.getFinish();
			}

			distanceActualToNext = glm::distance(nextCP, posActualCP);
		}

		if (pathFinished) {
			velocity->setMovable(false);
			continue;
		}

		glm::vec2 actualToNextCP = glm::normalize(glm::vec2(nextCP - posActualCP)) * distanceRemaining; // path to travel after last checkpoint passed
		glm::vec2 destination = posActualCP + actualToNextCP;

		vel = (destination - glm::vec2(transform->getPosition())) / elapsed;
		velocity->setVelocity(vel);
		path->setIndexNextCheckpoint(indexNextCheckpoint);
	}
}

bool AIFollowPathSystem::isGranted(Entity const & entity) const
{
	int cc(0);
	auto& compos = m_entityManager.getComponents(entity);
	for (auto const& compo : compos) {
		switch (compo->getType()) {
			case Component::Type::PATH:
			case Component::Type::VELOCITY:
			case Component::Type::TRANSFORM:
				cc++;
		}
	}
	return cc == 3;
}
