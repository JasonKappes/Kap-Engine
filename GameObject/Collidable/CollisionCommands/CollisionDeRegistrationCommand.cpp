#include "CollisionDeRegistrationCommand.h"
#include "CollidableAttorney.h"

CollisionDeRegistrationCommand::CollisionDeRegistrationCommand(Collidable* t_collidable)
{
	this->m_collidable = t_collidable;
}

void CollisionDeRegistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneCollisionDeRegistration(*this->m_collidable);
}
