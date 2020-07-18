#include <Matrix.h>
#ifndef _collisionvolume
#define _collisionvolume

class Model;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class CollisionVolume : public Align16
{
	friend class CollidableAttorney;
public:

	virtual void ComputeData(Model*, const Matrix&) = 0;
	virtual bool Intersect(const CollisionVolume&) const = 0;

	virtual bool IntersectAccept(const CollisionVolume& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeAABB& other) const = 0;
	virtual bool IntersectVisit(const CollisionVolumeOBB& other) const = 0;

	virtual void DebugView(const Vect& color) const = 0;
	virtual const Vect& GetCenter() const = 0;
	virtual float GetRadius() const = 0;
	virtual void SetModel(Model*) = 0;

	CollisionVolume() = default;
	CollisionVolume(const CollisionVolume&) = delete;
	~CollisionVolume() = default;


};

#endif _collisionvolume
#pragma once
