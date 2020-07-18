#include "CollisionVolumeOBB.h"
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

CollisionVolumeOBB::CollisionVolumeOBB(Model* t_model)
{
	this->m_center = t_model->getCenter();
	this->m_radius = t_model->getRadius();
}

void CollisionVolumeOBB::ComputeData()
{
	this->m_scale = Vect(max.X() - min.X(), max.Y() - min.Y(), max.Z() - min.Z());
	this->m_trans = 0.5f * (min + max);
	this->halfDiagonal = (max - min) * 0.5f;

	this->m_world = Matrix(SCALE, m_scale) * Matrix(IDENTITY) * Matrix(TRANS, m_trans);

	this->obbCenter = (min + halfDiagonal);
	this->squaredScale = m_world.get(ROW_0).mag() * m_world.get(ROW_0).mag();

	this->m_radius = std::abs((min.X() - max.X()));

	this->min = min;
	this->max = max;
}

void CollisionVolumeOBB::ComputeData(Model* t_model, const Matrix& t_world)
{
	this->m_world = t_world;
	this->m_center = t_model->getCenter() * t_world;
	this->m_radius = t_model->getRadius() * t_world.get(MatrixRowType::ROW_0).mag();

	this->min = t_model->getMinAABB();
	this->max = t_model->getMaxAABB();

	this->m_scale = Vect(max.X() - min.X(), max.Y() - min.Y(), max.Z() - min.Z());
	this->m_trans = 0.5f * (min + max);

	this->halfDiagonal = (max - min) * 0.5f;
	this->obbCenter = (min + halfDiagonal) * m_world;
	this->squaredScale = t_world.get(ROW_0).mag() * t_world.get(ROW_0).mag();

}

void CollisionVolumeOBB::SetModel(Model* t_model)
{
	this->m_center = t_model->getCenter();
}

void CollisionVolumeOBB::DebugView(const Vect& color) const
{
	VisualizerAttorney::Box::ShowOBB(*this, color);
}

bool CollisionVolumeOBB::Intersect(const CollisionVolume& ) const
{
	return false;
}

const Vect& CollisionVolumeOBB::GetHalfDiagonal() const
{
	return this->halfDiagonal;
}

float CollisionVolumeOBB::GetSquaredScale() const
{
	return this->squaredScale;
}

const Vect& CollisionVolumeOBB::GetOBBcenter() const
{
	return this->obbCenter;
}

const Vect& CollisionVolumeOBB::GetMin() const
{
	return this->min;
}

const Vect& CollisionVolumeOBB::GetMax() const
{
	return this->max;
}

const Vect& CollisionVolumeOBB::GetScale() const
{
	return this->m_scale;
}

const Vect& CollisionVolumeOBB::GetTrans() const
{
	return this->m_trans;
}

bool CollisionVolumeOBB::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return KapMathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return KapMathTools::Intersect(*this, other);
}

bool CollisionVolumeOBB::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return KapMathTools::Intersect(other, *this);
}

const Vect& CollisionVolumeOBB::GetCenter() const
{
	return this->m_center;
}

const Matrix& CollisionVolumeOBB::GetWorld() const
{
	return this->m_world;
}

float CollisionVolumeOBB::GetRadius() const
{
	return this->m_radius;
}
