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

	/// <summary>
	/// Takes a Vect and returns the magnitude
	/// </summary> 
	/// \ingroup MathTools
	static float Magnitude(const Vect&);

	/// <summary>
	/// Given a point, min, and max... it returns a clamped coordinate
	/// </summary> 
	/// \ingroup MathTools
	static float CalculateClampCoordinate(float value, float minValue, float maxValue);

	/// <summary>
	/// Given a Vect, min Vect, and max Vect... it returns a clamped Vect (3D point)
	/// </summary> 
	/// \ingroup MathTools
	static Vect GetClampedVect(const Vect& point, const Vect& min, const Vect& max);

	/// <summary>
	/// Returns a maximum OBB projection value
	/// </summary> 
	/// \ingroup MathTools
	static float MaxOBBProjection(const Matrix& world, const Vect& half_diagonal, float square_scale, const Vect& v);

	/// <summary>
	/// Returns the correct signature given two vectors
	/// </summary> 
	/// \ingroup MathTools
	static Vect Signature(const Vect& v, const Vect& d);

	/// <summary>
	/// Given a Vect, min Vect, and max Vect... it returns a clamped Vect (3D point)
	/// </summary> 
	/// \ingroup MathTools
	static float EuclidianNorm(const Vect&);

	/// <summary>
	/// Given ray information and plane information, return a point of contact on the plane
	/// </summary> 
	/// \ingroup MathTools
	static Vect LinePlaneIntersection(const Vect& raypoint, const Vect& raydirection, const Vect& planepoint, const Vect& planenormal);

	/// <summary>
	/// Binary predicate that checks if a point is inside of a sphere.
	/// </summary> 
	/// \ingroup MathTools
	static bool IsPointInSphere(const Vect& sphereCenter, float sphereRadius, const Vect& otherPoint);

	/// <summary>
	/// Takes a two collision volumes and detects if there is a collision
	/// </summary> 
	/// \ingroup MathTools
	static bool Intersect(const CollisionVolume&, const CollisionVolume&);

	/// <summary>
	/// Takes a two collision spheres and detects if there is a collision
	/// </summary> 
	/// \ingroup MathTools
	static bool Intersect(const CollisionVolumeBSphere&, const CollisionVolumeBSphere&);

	/// <summary>
	/// Takes a two collision AABB's and detects if there is a collision
	/// </summary> 
	/// \ingroup MathTools
	static bool Intersect(const CollisionVolumeAABB&, const CollisionVolumeAABB&);

	/// <summary>
	/// Takes a two collision OBB's and detects if there is a collision
	/// </summary> 
	/// \ingroup MathTools
	static bool Intersect(const CollisionVolumeOBB&, const CollisionVolumeOBB&);

	/// <summary>
	/// Takes an OBB and an AABB and detects if there is a collision
	/// </summary> 
	/// \ingroup MathTools
	static bool Intersect(const CollisionVolumeOBB&, const CollisionVolumeAABB&);

	/// <summary>
	/// Takes an AABB and a sphere and detects if there is a collision
	/// </summary> 
	/// \ingroup MathTools
	static bool Intersect(const CollisionVolumeBSphere&, const CollisionVolumeAABB&);

	/// <summary>
	/// Takes an AABB and an OBB and detects if there is a collision
	/// </summary> 
	/// \ingroup MathTools
	static bool Intersect(const CollisionVolumeBSphere&, const CollisionVolumeOBB&);

private:
	KapMathTools() = delete;
	KapMathTools(const KapMathTools&) = delete;
	KapMathTools operator=(const KapMathTools&) = delete;
	~KapMathTools() = delete;
};

#endif _kapmathtools
#pragma once
