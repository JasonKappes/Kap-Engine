#ifndef _collidableattorney
#define _collidableattorney
#include "Matrix.h"

class Collidable;
class CollisionVolume;
class CollisionVolumeBSphere;
class TerrainModel;

class CollidableAttorney
{
public:
	class Registration
	{
		friend class CollisionRegistrationCommand;
		friend class CollisionDeRegistrationCommand;
	private:
		static void SceneCollisionRegistration(Collidable&);
		static void SceneCollisionDeRegistration(Collidable&);

	private:
		Registration() = delete;
		Registration(const Registration&) = delete;
		Registration operator=(const Registration&) = delete;
		~Registration() = delete;
	};

	class GameLoop
	{
		friend class CollidableGroup;
	private:
		static float GetRadius(const Collidable&);
		static const Vect& GetCenter(const Collidable&);
	};

	class Collision
	{
		friend class CollisionTestSelfCommand;
		friend class CollisionTestPairCommand;
		friend class CollisionTestTerrainCommand;
		friend class CollidableGroup;
		friend class PlayerTank;
	private:
		static const CollisionVolume& GetCollisionVolume(Collidable&);
		static const CollisionVolumeBSphere& GetDefaultBSphere(Collidable&);

	private:
		Collision() = delete;
		Collision(const Collision&) = delete;
		Collision operator=(const Collision&) = delete;
		~Collision() = delete;
	};

private:
	CollidableAttorney() = delete;
	CollidableAttorney(const CollidableAttorney&) = delete;
	CollidableAttorney operator=(const CollidableAttorney&) = delete;
	~CollidableAttorney() = delete;
};

#endif _collidableattorney
#pragma once
