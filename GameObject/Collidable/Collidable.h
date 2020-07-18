#ifndef _collidable
#define _collidable
#include "AzulCore.h"
#include "EventType.h"
#include "CollidableManager.h"
#include "CollidableGroup.h"
#include "SceneAttorney.h"
#include "Registration.h"

class CollisionRegistrationCommand;
class CollisionDeRegistrationCommand;
class CollisionVolume;
class CollisionVolumeBSphere;

class Collidable
{
    friend class CollidableAttorney;

public:
    enum class Volume
    {
        BSPHERE, AABB, OBB
    };

protected:
    /// <summary>
    /// Called by a GameObject to register its model for collision against any paired-collision GameObjects.
    /// </summary> 
    /// \ingroup Collidable
    void SubmitCollisionRegistration();

    /// <summary>
    /// Called by a GameObject to deregister its specific model for all collisions.
    /// </summary> 
    /// \ingroup Collidable
    void SubmitCollisionDeRegistration();

    /// <summary>
    /// If a GameObject wants to be registered for collision, it must set a collider model that can be utilized for collision detection.
    /// </summary> 
    /// \ingroup Collidable
    void SetColliderModel(Model* collisionModel, Volume chosenCollisionVolume = Volume::BSPHERE);

    /// <summary>
    /// To be called by a GameObject to gets its current collision model
    /// </summary> 
    /// \ingroup Collidable
    Model* GetColliderModel();

    /// <summary>
    /// This method must be called every frame (in Update) for a GameObject registered for colliison.
    /// It assists the engine in accurate collision detection between models.
    /// </summary> 
    /// \ingroup Collidable
    void UpdateCollisionData(const Matrix& worldMatrix);

protected:
    Collidable();
    Collidable(const Collidable&) = delete;
    virtual ~Collidable();

private:
    /// <summary>
    /// This method should be overriden by a GameObject with another GameObject as the parameter. 
    /// Collision between the two GameObjects will call this function, if there is the correct derived class parameter.
    /// 
    /// Recommended Syntax: void Collision(AnotherGameObject* Specific_GameObjectCollidedWith) override
    /// Recommended Syntax: void Collision(Collidable* GeneralCollisionDetected) override
    /// </summary> 
    /// \ingroup Collidable
    virtual void Collision(Collidable*) { DebugMsg::out(" \n Base Collidable COLLISION: UH OH!"); }

    virtual void CollisionTerrain() { DebugMsg::out(" \n Base Collidable TERRAIN COLLISION: uh oh!"); }

    const CollisionVolume& GetCollisionVolume() const;

    const CollisionVolumeBSphere& GetDefaultBSphere() const;

    const Vect& GetCenter() const;

    float GetRadius() const;

    void SceneCollisionRegistration();
    void SceneCollisionDeRegistration();

private:
    CollidableManager::PWTypeID m_CollidableId = CollidableManager::PWID_UNDEFINED;
    CollidableGroup::CollidableCollectionRef m_delRef;
    RegistrationState m_CollRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
    CollisionRegistrationCommand* m_collisionRegistrationCommand;
    CollisionDeRegistrationCommand* m_collisionDeRegistrationCommand;
    CollisionVolume* m_CollVolume;
    CollisionVolumeBSphere* m_DefaultSphereVolume;
    Model* m_CollidableModel;

protected:

    template < typename C>
    void SetCollidableGroup()
    {
        m_CollidableId = SceneAttorney::Registration::GetCollidableMgr()->GetInstanceID<C>();
    }
};

#endif _collidable
#pragma once