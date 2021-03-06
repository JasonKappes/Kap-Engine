#ifndef _raycast
#define _raycase
#include "Vect.h"
#include "Matrix.h"
#include "Camera.h"

class Raycast
{
public:
	Raycast() = default;
	Raycast(const Raycast&) = delete;
	Raycast operator=(const Raycast&) = delete;
	~Raycast() = default;

	/// Detects a collision between a BSPHERE and the mouse
	static bool MouseSphereCollision(Vect pos, float rad);

	/// Detects a collision between an OBB and the mouse
	static bool MouseBoxCollision(const Vect& min, const Vect& max);

	/// Get a ray coming from the mouse
	static Vect GetMouseWorldSpaceRay();

private:
	static Vect Get3DRay(float mousex, float mousey);
	static Vect GetEyeSpaceCoordinates(Vect& clipCoords);
	static Vect GetWorldSpaceCoordinates(Vect& eyeSpaceCoords);
	static Vect GetWorldSpaceCoordinatesNonNormalized(Vect& eyeSpaceCoords);
	static bool CheckForCollision(Vect pos, Vect ray, float rad);
	static bool CheckForCollision(const Vect& ray, const Vect& min, const Vect& max);
	static float dot(Vect a, Vect b);
private:
	Vect m_currentRay;
	Matrix m_proj;
	Matrix m_view;


};

#endif _raycast
#pragma once
