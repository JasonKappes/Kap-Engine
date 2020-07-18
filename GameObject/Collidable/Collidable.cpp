#include "Collidable.h"
#include "CollisionRegistrationCommand.h"
#include "CollisionDeRegistrationCommand.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "CollisionVolumeBSphere.h"
#include "CollisionVolumeAABB.h"
#include "CollisionVolumeOBB.h"

Collidable::Collidable()
{
	this->m_collisionRegistrationCommand = new CollisionRegistrationCommand(this);
	this->m_collisionDeRegistrationCommand = new CollisionDeRegistrationCommand(this);
	this->m_CollidableModel = nullptr;
	this->m_CollVolume = nullptr;
}

void Collidable::SceneCollisionRegistration()
{
	DebugMsg::out("\n COLLIDABLE: -----> Registration ");
	assert(this->m_CollRegistrationState == RegistrationState::PENDING_REGISTRATION);
	this->m_CollRegistrationState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Registration::GetCollidableMgr()->GetCollisionGroup(this->m_CollidableId)->Register(this, this->m_delRef);
}

void Collidable::SceneCollisionDeRegistration()
{
	DebugMsg::out("\n COLLIDABLE, GROUP: %d : -----> De - Registration ", this->m_CollidableId);
	assert(this->m_CollRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	this->m_CollRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Registration::GetCollidableMgr()->GetCollisionGroup(this->m_CollidableId)->DeRegister(this->m_delRef);
}

const CollisionVolume& Collidable::GetCollisionVolume() const
{
	return *this->m_CollVolume;
}

const CollisionVolumeBSphere& Collidable::GetDefaultBSphere() const
{
	return *this->m_DefaultSphereVolume;
}

const Vect& Collidable::GetCenter() const
{
	return this->GetCollisionVolume().GetCenter();
}

float Collidable::GetRadius() const
{
	return this->GetCollisionVolume().GetRadius();
}

void Collidable::SetColliderModel(Model* t_model, Collidable::Volume t_volume)
{
	this->m_CollidableModel = t_model;
	this->m_DefaultSphereVolume = new CollisionVolumeBSphere(t_model);
	switch (t_volume)
	{
	case Collidable::Volume::BSPHERE:
		if (m_CollVolume != nullptr)
		{
			this->m_CollVolume->SetModel(t_model);
		}
		else {
			this->m_CollVolume = new CollisionVolumeBSphere(this->m_CollidableModel);
		}
		break;
	case Collidable::Volume::AABB:
		if (m_CollVolume != nullptr)
		{
			this->m_CollVolume->SetModel(t_model);
		}
		else {
			this->m_CollVolume = new CollisionVolumeAABB(this->m_CollidableModel);
		}
		break;
	case Collidable::Volume::OBB:
		if (m_CollVolume != nullptr)
		{
			this->m_CollVolume->SetModel(t_model);
		}
		else {
			this->m_CollVolume = new CollisionVolumeOBB(this->m_CollidableModel);
		}
		break;
	default:
		break;
	}
}

Model* Collidable::GetColliderModel()
{
	return this->m_CollidableModel;
}

void Collidable::UpdateCollisionData(const Matrix& t_world)
{
	this->m_CollVolume->ComputeData(this->m_CollidableModel, t_world);
	this->m_DefaultSphereVolume->ComputeData(this->m_CollidableModel, t_world);
}

void Collidable::SubmitCollisionRegistration()
{
	assert(this->m_CollRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	this->m_CollRegistrationState = RegistrationState::PENDING_REGISTRATION;

	SceneManager::GetCurrentScene()->SubmitCommand(this->m_collisionRegistrationCommand);
}

void Collidable::SubmitCollisionDeRegistration()
{
	assert(this->m_CollRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	this->m_CollRegistrationState = RegistrationState::PENDING_DEREGISTRATION;

	SceneManager::GetCurrentScene()->SubmitCommand(this->m_collisionDeRegistrationCommand);
}

Collidable::~Collidable()
{
	delete this->m_collisionRegistrationCommand;
	delete this->m_collisionDeRegistrationCommand;

	if (m_CollVolume != nullptr)
	{
		delete this->m_CollVolume;
		delete this->m_DefaultSphereVolume;
	}
}