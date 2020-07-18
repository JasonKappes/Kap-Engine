#ifndef _collisionvolumebsphere
#define _collisionvolumebsphere
#include "CollisionVolume.h"

class CollisionVolumeBSphere : public CollisionVolume
{
	friend class CollidableAttorney;
public:
	CollisionVolumeBSphere();
	CollisionVolumeBSphere(Model*);
	CollisionVolumeBSphere(const CollisionVolumeBSphere&) = delete;
	~CollisionVolumeBSphere() = default;

	virtual bool IntersectAccept(const CollisionVolume& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere& other) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB&) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB&) const override;

	void ComputeData(Model*, const Matrix&) override;
	void SetModel(Model*) override;
	void DebugView(const Vect& color) const override;

	const Vect& GetCenter() const override;
	const Matrix& GetWorld() const;

	float GetRadius() const override;

	bool Intersect(const CollisionVolume&) const override;

private:
	Vect m_center;
	float m_radius;
	Matrix m_world;
};

#endif _collisionvolumebsphere
#pragma once
