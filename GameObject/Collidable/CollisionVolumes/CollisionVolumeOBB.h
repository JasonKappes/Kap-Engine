#ifndef _collisionvolumeobb
#define _collisionvolumeobb
#include "CollisionVolume.h"

class GraphicsObject_WireframeConstantColor;

class CollisionVolumeOBB : public CollisionVolume
{
	friend class CollidableAttorney;
public:
	CollisionVolumeOBB() = delete;
	CollisionVolumeOBB(Model*);
	CollisionVolumeOBB(const CollisionVolumeOBB&) = delete;
	~CollisionVolumeOBB() = default;

	const Vect& GetMin() const;
	const Vect& GetMax() const;
	const Vect& GetScale() const;
	const Vect& GetTrans() const;

	virtual bool IntersectAccept(const CollisionVolume&) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB&) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB&) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere&) const override;

	void ComputeData(Model*, const Matrix&) override;
	void ComputeData();
	void SetModel(Model*) override;
	void DebugView(const Vect& color) const override;

	const Vect& GetCenter() const override;
	const Matrix& GetWorld() const;

	float GetRadius() const override;
	bool Intersect(const CollisionVolume&) const override;

	const Vect& GetHalfDiagonal() const;
	float GetSquaredScale() const;
	const Vect& GetOBBcenter() const;

	void SetPosition(Vect tpos) { this->m_position = tpos; }
	void SetRotation(Matrix& trot) { this->m_rotation = trot; }
	void SetMin(Vect tmin) { this->min = tmin; }
	void SetMax(Vect tmax) { this->max = tmax; }

private:
	GraphicsObject_WireframeConstantColor* goc;

	Vect min;
	Vect max;

	Vect halfDiagonal;
	float squaredScale;
	Vect obbCenter;

	Vect m_scale;
	Vect m_center;
	float m_radius;
	Matrix m_world;
	Matrix m_rotation;
	Vect m_position;
	Vect m_trans;
};

#endif _collisionvolumeobb
#pragma once
