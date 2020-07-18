#include "CollisionRegistrationCommand.h"
#include "CollidableAttorney.h"

CollisionRegistrationCommand::CollisionRegistrationCommand(Collidable* t_collidable)
{
	this->m_collidable = t_collidable;
}

void CollisionRegistrationCommand::Execute()
{
	CollidableAttorney::Registration::SceneCollisionRegistration(*this->m_collidable);
}
