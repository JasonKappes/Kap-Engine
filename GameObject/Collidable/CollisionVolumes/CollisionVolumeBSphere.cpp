#include "CollisionVolumeBSphere.h"
#include "Matrix.h"
#include "Model.h"
#include <DebugOut.h>
#include "KapMathTools.h"
#include "VisualizerAttorney.h"

CollisionVolumeBSphere::CollisionVolumeBSphere() : m_center(Vect(0, 0, 0)), m_radius(0.0f), m_world(Matrix(IDENTITY)) {}

CollisionVolumeBSphere::CollisionVolumeBSphere(Model* t_model)
{
	this->m_center = t_model->getCenter();
	this->m_radius = t_model->getRadius();
}

void CollisionVolumeBSphere::ComputeData(Model* t_model, const Matrix& t_world)
{
	this->m_center = t_model->getCenter() * t_world;
	this->m_radius = t_model->getRadius() * t_world.get(MatrixRowType::ROW_0).mag();
	this->m_world = t_world;
}

void CollisionVolumeBSphere::SetModel(Model* t_model)
{
	this->m_center = t_model->getCenter();
}

void CollisionVolumeBSphere::DebugView(const Vect& color) const
{
	VisualizerAttorney::Sphere::ShowBSphere(*this, color);
}

bool CollisionVolumeBSphere::Intersect(const CollisionVolume& ) const
{
	return false;
}

bool CollisionVolumeBSphere::IntersectAccept(const CollisionVolume& other) const
{
	return other.IntersectVisit(*this);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeBSphere& other) const
{
	return KapMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeAABB& other) const
{
	return KapMathTools::Intersect(*this, other);
}

bool CollisionVolumeBSphere::IntersectVisit(const CollisionVolumeOBB& other) const
{
	return KapMathTools::Intersect(*this, other);
}

const Vect& CollisionVolumeBSphere::GetCenter() const
{
	return this->m_center;
}

const Matrix& CollisionVolumeBSphere::GetWorld() const
{
	return this->m_world;
}

float CollisionVolumeBSphere::GetRadius() const
{
	return this->m_radius;
}
