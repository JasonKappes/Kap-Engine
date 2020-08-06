#ifndef _kapmathtools
#define _kapmathtools
#include "Matrix.h"

class CollisionVolume;
class CollisionVolumeBSphere;
class CollisionVolumeAABB;
class CollisionVolumeOBB;

class KapMathTools
{
	friend class MathToolsAttorney;
public:

	/// Given a point, min, and max... it returns a clamped coordinate
	static float CalculateClampCoordinate(float value, float minValue, float maxValue);

	/// Given a Vect, min Vect, and max Vect... it returns a clamped Vect (3D point)
	static Vect GetClampedVect(const Vect& point, const Vect& min, const Vect& max);

	/// Returns a maximum OBB projection value
	static float MaxOBBProjection(const Matrix& world, const Vect& half_diagonal, float square_scale, const Vect& v);

	/// Returns the correct signature given two vectors
	static Vect Signature(const Vect& v, const Vect& d);

	/// Returns the length of the vector
	static float EuclidianNorm(const Vect&);

	/// Given ray information and plane information, return a point of contact (3D point) on the plane
	static Vect LinePlaneIntersection(const Vect& raypoint, const Vect& raydirection, const Vect& planepoint, const Vect& planenormal);

	/// Binary predicate that checks if a point is inside of a sphere.
	static bool IsPointInSphere(const Vect& sphereCenter, float sphereRadius, const Vect& otherPoint);

	/// Binary predicate that returns if there is a collision between two collision volumes (First part of visitor pattern)
	static bool Intersect(const CollisionVolume&, const CollisionVolume&);

	/// Binary predicate that detects if there is a collision between two spheres
	static bool Intersect(const CollisionVolumeBSphere&, const CollisionVolumeBSphere&);

	/// Binary preicate that takes a two collision AABB's and detects if there is a collision
	static bool Intersect(const CollisionVolumeAABB&, const CollisionVolumeAABB&);

	/// Binary predicate that takes two collision OBB's and detects if there is a collision
	static bool Intersect(const CollisionVolumeOBB&, const CollisionVolumeOBB&);

 	/// Binary predicate that takes an OBB and an AABB and detects if there is a collision
	static bool Intersect(const CollisionVolumeOBB&, const CollisionVolumeAABB&);

	/// Binary predicate that takes an AABB and a sphere and detects if there is a collision
	static bool Intersect(const CollisionVolumeBSphere&, const CollisionVolumeAABB&);

	/// Binary predicate that takes an AABB and an OBB and detects if there is a collision
	static bool Intersect(const CollisionVolumeBSphere&, const CollisionVolumeOBB&);

private:
	KapMathTools() = delete;
	KapMathTools(const KapMathTools&) = delete;
	KapMathTools operator=(const KapMathTools&) = delete;
	~KapMathTools() = delete;
};

#endif _kapmathtools
#pragma once
