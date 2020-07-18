#ifndef _collisionvolumeaabb
#define _collisionvolumeaabb
#include "CollisionVolume.h"

class GraphicsObject_WireframeConstantColor;

class CollisionVolumeAABB : public CollisionVolume
{
	friend class CollidableAttorney;
public:
	CollisionVolumeAABB();
	CollisionVolumeAABB(Model*);
	CollisionVolumeAABB(const CollisionVolumeAABB&) = delete;
	CollisionVolumeAABB operator=(const CollisionVolumeAABB&) = delete;
	~CollisionVolumeAABB() = default;

	bool operator==(const CollisionVolumeAABB&) const;


	const Vect& GetMin() const;
	const Vect& GetMax() const;
	const Vect& GetScale() const;
	const Vect& GetTrans() const;

	void SetMin(Vect tmin) { this->min = tmin; }
	void SetMax(Vect tmax) { this->max = tmax;  }
	void SetScale(Vect tscale) { this->m_scale = tscale;  }
	void SetTrans(Vect ttrans) { this->m_trans = ttrans;  }
	void SetHalfDiagonal(Vect thd) { this->halfDiagonal = thd; }
	void SetRotation(Matrix trot) { this->m_rotation = trot; }
	void SetPosition(Vect tpos) { this->m_position = tpos; }

	virtual bool IntersectAccept(const CollisionVolume&) const override;
	virtual bool IntersectVisit(const CollisionVolumeAABB&) const override;
	virtual bool IntersectVisit(const CollisionVolumeBSphere&) const override;
	virtual bool IntersectVisit(const CollisionVolumeOBB&) const override;

	void ComputeData(Model*, const Matrix&) override;
	void SetModel(Model*) override;
	void DebugView(const Vect& color) const override;

	const Vect& GetCenter() const override;
	const Matrix& GetWorld() const;

	float GetRadius() const override;
	bool Intersect(const CollisionVolume&) const override;

	const Vect& GetHalfDiagonal() const;
	float GetSquaredScale() const;
	const Vect& GetOBBcenter() const;
	void MinMaxOBBData();

	void CalculateTrans();
	void CalculateScale();

private:
	void CalculateMinMax(Model*,const Matrix&);
	void CalculateOBBdata(Model*, const Matrix&);

private:
	GraphicsObject_WireframeConstantColor* goc;
	Vect min;
	Vect max;
	Vect obbmin;
	Vect obbmax;
	Vect m_position;

	Vect halfDiagonal;
	float squaredScale;
	Vect obbCenter;

	Vect m_scale;
	Vect m_center;
	float m_radius;
	Matrix m_world;
	Matrix m_rotation;
	Vect m_trans;
};

#endif _collisionvolumeaabb
#pragma once
