#include "CollidableAttorney.h"
#include "Collidable.h"
#include "CollisionVolumeBSphere.h"

void CollidableAttorney::Registration::SceneCollisionRegistration(Collidable& t_collidable)
{
	t_collidable.SceneCollisionRegistration();
}

void CollidableAttorney::Registration::SceneCollisionDeRegistration(Collidable& t_collidable)
{
	t_collidable.SceneCollisionDeRegistration();
}

const CollisionVolume& CollidableAttorney::Collision::GetCollisionVolume(Collidable& t_collidable)
{
	return t_collidable.GetCollisionVolume();
}

const CollisionVolumeBSphere& CollidableAttorney::Collision::GetDefaultBSphere(Collidable& t_collidable)
{
	return t_collidable.GetDefaultBSphere();
}

float CollidableAttorney::GameLoop::GetRadius(const Collidable& t_collidable)
{
	return t_collidable.GetRadius();
}

const Vect& CollidableAttorney::GameLoop::GetCenter(const Collidable& t_collidable)
{
	return t_collidable.GetCenter();
}
