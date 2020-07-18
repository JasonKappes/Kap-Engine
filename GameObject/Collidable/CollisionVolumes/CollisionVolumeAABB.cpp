#include "CollisionVolumeAABB.h"
#include "Matrix.h"
#include "Model.h"
#include <DebugOut.h>
#include "KapMathTools.h"
#include "VisualizerAttorney.h"
#include "ShaderManager.h"
#include "ModelManager.h"
#include "GraphicsObject_WireframeConstantColor.h"
#include <SceneManager.h>
#include "Raycast.h"
#include "CollisionVolumeBSphere.h"

CollisionVolumeAABB::CollisionVolumeAABB() : m_center(Vect(0, 0, 0)), m_radius(0.0f) {}

CollisionVolumeAABB::CollisionVolumeAABB(Model* t_model)
{
	this->m_center = t_model->getCenter();
	this->m_radius = t_model->getRadius();
}

bool CollisionVolumeAABB::operator==(const CollisionVolumeAABB& v) const
{
	if (min.isEqual(v.min) &&
		max.isEqual(v.max) &&
		obbmin.isEqual(v.obbmin) &&
		obbmax.isEqual(v.obbmax) &&
		m_position.isEqual(v.m_position) &&
		halfDiagonal.isEqual(v.halfDiagonal) &&
		squaredScale == v.squaredScale &&
		obbCenter.isEqual(v.obbCenter) &&
		m_scale.isEqual(v.m_scale) &&
		m_center.isEqual(v.m_center) &&
		m_radius == v.m_radius &&
		m_world.isEqual(v.m_world) &&
		m_rotation.isEqual(v.m_rotation) &&
		m_trans.isEqual(v.m_trans))
	{
		return true;
	}
	else {
		return false;
	}
}

void CollisionVolumeAABB::CalculateMinMax(Model* t_model, const Matrix& world)
{
	Vect* indList = t_model->getVectList();

	Vect start = indList[0] * world;

	float maxx = start.X();
	float maxy = start.Y();
	float maxz = start.Z();
	float minx = start.X();
	float miny = start.Y();
	float minz = start.Z();

	for (int ind = 1; ind < t_model->getTriNum(); ++ind)
	{
		Vect v = indList[ind];
		v = v * world;
		if (v.X() > maxx)		maxx = v.X();
		if (v.X() < minx)  minx = v.X();

		if (v.Y() > maxy)		maxy = v.Y();
		if (v.Y() < miny)  miny = v.Y();

		if (v.Z() > maxz)		maxz = v.Z();
		if (v.Z() < minz)  minz = v.Z();
	}

	this->min = Vect(minx, miny, minz);
	this->max = Vect(maxx, maxy, maxz);

	CalculateScale();
	CalculateTrans();
}

void CollisionVolumeAABB::MinMaxOBBData() //no model
{
	this->m_scale = Vect(max.X() - min.X(), 0.0f, max.Z() - min.Z());
	this->m_trans = 0.5f * (min + max);
	this->halfDiagonal = (max - min) * 0.5f;

	this->m_world = Matrix(IDENTITY);
	this->obbCenter = (min + halfDiagonal);
	this->squaredScale = m_world.get(ROW_0).mag() * m_world.get(ROW_0).mag();

	this->m_radius = std::abs((min.X() - max.X()));
}

void CollisionVolumeAABB::ComputeData(Model* t_model, const Matrix& t_world)
{
	//AABB-level data
	CalculateMinMax(t_model, t_world);
	this->m_world = t_world;
	this->m_center = t_model->getCenter() * t_world;
	this->m_radius = t_model->getRadius() * t_world.get(MatrixRowType::ROW_0).mag();

	//OBB-level data
	CalculateOBBdata(t_model, t_world);
}

void CollisionVolumeAABB::CalculateOBBdata(Model* t_model, const Matrix& t_world)
{
	obbmin = t_model->getMinAABB();
	obbmax = t_model->getMaxAABB();

	this->halfDiagonal = (obbmax - obbmin) * 0.5f;
	this->obbCenter = (obbmin + halfDiagonal) * m_world;
	this->squaredScale = t_world.get(ROW_0).mag() * t_world.get(ROW_0).mag();
}

void CollisionVolumeAABB::CalculateScale()
{
	this->m_scale = Vect(max.X() - min.X(), max.Y() - min.Y(), max.Z() - min.Z());
}


void CollisionVolumeAABB::CalculateTrans()
{
	this->m_trans = 0.5f * (min + max);
}

void CollisionVolumeAABB::SetModel(Model* t_model)
{
	this->m_center = t_model->getCenter();
}

void CollisionVolumeAABB::DebugView(const Vect& color) const
{
	VisualizerAttorney::Box::ShowAABB(*this, color);
}

bool CollisionVolumeAABB::Intersect(const CollisionVolume&) const
{
	return false;
}

const Vect& CollisionVolumeAABB::GetMin() const
{
	return this->min;
}

const Vect& CollisionVolumeAABB::GetMax() const
{
	return this->max;
}

const Vect& CollisionVolumeAABB::GetScale() const
{
	return this->m_scale;
}

const Vect& CollisionVolumeAABB::GetTrans() const
{
	return this->m_trans;
}

const Vect& CollisionVolumeAABB::GetHalfDiagonal() const
{
	return this->halfDiagonal;
}

float CollisionVolumeAABB::GetSquaredScale() const
{
	return this->squaredScale;
}

const Vect& CollisionVolumeAABB::GetOBBcenter() const
{
	return this->obbCenter;
}

bool CollisionVolumeAABB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return KapMathTools::Intersect(*this, other);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return KapMathTools::Intersect(other, *this);
}

bool CollisionVolumeAABB::IntersectVisit(const CollisionVolumeOBB& box) const
{
	return KapMathTools::Intersect(box, *this);
}

const Vect& CollisionVolumeAABB::GetCenter() const
{
	return this->m_center;
}

const Matrix& CollisionVolumeAABB::GetWorld() const
{
	return this->m_world;
}

float CollisionVolumeAABB::GetRadius() const
{
	return this->m_radius;
}
