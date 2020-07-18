#include "Raycast.h"
#include "KapEngine.h"
#include "SceneManager.h"
#include "Scene.h"
using namespace std;

bool Raycast::MouseSphereCollision(Vect pos, float rad)
{
	int t_mouseX;
	int t_mouseY;

	//mouse position goes into the local int variables
	KapEngine::GetMousePosition(t_mouseX, t_mouseY);

	//get a 3D ray from openGL coordinates
	Vect clipRay = Get3DRay((float)t_mouseX, (float)t_mouseY);

	//convert ray to eye space coordinates
	Vect eyeSpaceRay = GetEyeSpaceCoordinates(clipRay);

	//convert to world space coordinates
	Vect worldSpaceRay = GetWorldSpaceCoordinates(eyeSpaceRay);

	bool coll = CheckForCollision(pos, worldSpaceRay, rad);

	return coll;
}

bool Raycast::MouseBoxCollision(const Vect& min, const Vect& max)
{
	int t_mouseX;
	int t_mouseY;

	//mouse position goes into the local int variables
	Engine::getMousePosition(t_mouseX, t_mouseY);

	//get a 3D ray from openGL coordinates
	Vect clipRay = Get3DRay((float)t_mouseX, (float)t_mouseY);

	//convert ray to eye space coordinates
	Vect eyeSpaceRay = GetEyeSpaceCoordinates(clipRay);

	//convert to world space coordinates
	Vect worldSpaceRay = GetWorldSpaceCoordinates(eyeSpaceRay);

	bool coll = CheckForCollision(worldSpaceRay, min, max);

	return coll;
}

bool Raycast::CheckForCollision(const Vect& ray, const Vect& mn, const Vect& mx)
{
	//ray direction
	Vect dirFrax = Vect(1.0f / ray.X(), 1.0f / ray.Y(), 1.0f / ray.Z());

	//ray origin
	Vect origin = Vect();
	SceneManager::Get3DCamera()->getPos(origin);

	float t1 = (mn.X() - origin.X()) * dirFrax.X();
	float t2 = (mx.X() - origin.X()) * dirFrax.X();
	float t3 = (mn.Y() - origin.Y()) * dirFrax.Y();
	float t4 = (mx.Y() - origin.Y()) * dirFrax.Y();
	float t5 = (mn.Z() - origin.Z()) * dirFrax.Z();
	float t6 = (mx.Z() - origin.Z()) * dirFrax.Z();

	float tmin = max(max(min(t1, t2), min(t3, t4)), min(t5, t6));
	float tmax = min(min(max(t1, t2), max(t3, t4)), max(t5, t6));

	// if tmax < 0, ray (line) is intersecting AABB, but the whole AABB is behind us
	if (tmax < 0)
	{
		//t = tmax;
		return false;
	}

	// if tmin > tmax, ray doesn't intersect AABB
	if (tmin > tmax)
	{
		//t = tmax;
		return false;
	}

	//t = tmin;
	return true;
}

bool Raycast::CheckForCollision(Vect center, Vect ray, float rad)
{
	Vect origin = Vect();
	SceneManager::Get3DCamera()->getPos(origin);
	Vect originToCenter = origin - center;
	float b = dot(ray,originToCenter);
	float c = dot(originToCenter, originToCenter) - (rad * rad);
	float value = (b * b) - c;

	return value > 0;
}

float Raycast::dot(Vect a, Vect b)
{
	return (a.X() * b.X()) + (a.Y() * b.Y()) + (a.Z() * b.Z());
}

Vect Raycast::Get3DRay(float t_mouseX, float t_mouseY)
{
	// Get Normalized Device Coordinates (OpenGL coords)
	float t_x = ((2.0f * t_mouseX) / KapEngine::GetWindowWidth()) - 1.0f;
	float t_y = 1.0f - ((2.0f * t_mouseY) / KapEngine::GetWindowHeight());

	Vect ray = Vect(t_x, t_y, -1.0f, 1.0f);

	//return a ray, with Z coordinate pointing into the screen
	return ray;

}

Vect Raycast::GetEyeSpaceCoordinates(Vect& ray)
{
	//copy projection matrix
	Matrix m(SceneManager::Get3DCamera()->getProjMatrix());

	m.inv();

	float vx = m.M0() * ray.X() + m.M1() * ray.Y() + m.M2() * ray.Z() + m.M3() * ray.W();
	float vy = m.M4() * ray.X() + m.M5() * ray.Y() + m.M6() * ray.Z() + m.M7() * ray.W();
	float vz = -1.0f;
	float vw = 1.0f;
	
	Vect eyeRay = Vect(vx, vy, vz, vw).norm();

	eyeRay *= SceneManager::GetCurrentScene()->GetCamRotation();

	return eyeRay; //center screen ray
}

Vect Raycast::GetMouseWorldSpaceRay()
{
	int t_mouseX;
	int t_mouseY;

	//mouse position goes into the local int variables
	KapEngine::GetMousePosition(t_mouseX, t_mouseY);

	//get a 3D ray from openGL coordinates
	Vect clipRay = Get3DRay((float)t_mouseX, (float)t_mouseY);

	//convert ray to eye space coordinates
	Vect eyeSpaceRay = GetEyeSpaceCoordinates(clipRay);

	//convert to world space coordinates
	Vect worldSpaceRay = GetWorldSpaceCoordinates(eyeSpaceRay);

	return worldSpaceRay;
}


Vect Raycast::GetWorldSpaceCoordinates(Vect& ray)
{
	Matrix m(SceneManager::Get3DCamera()->getViewMatrix());
	m.inv();

	float vx = m.M0() * ray.X() + m.M1() * ray.Y() + m.M2() * ray.Z() + m.M3() * ray.W();
	float vy = m.M4() * ray.X() + m.M5() * ray.Y() + m.M6() * ray.Z() + m.M7() * ray.W();
	float vz = m.M8() * ray.X() + m.M9() * ray.Y() + m.M10() * ray.Z() + m.M11() * ray.W();
	float vw = 1.0f;

	Vect worldRay = Vect(vx, vy, vz, vw).norm();

	worldRay *= SceneManager::GetCurrentScene()->GetCamRotation();

	return worldRay;
}

Vect Raycast::GetWorldSpaceCoordinatesNonNormalized(Vect& ray)
{

	Matrix m(SceneManager::Get3DCamera()->getViewMatrix());
	m.inv();

	float vx = m.M0() * ray.X() + m.M1() * ray.Y() + m.M2() * ray.Z() + m.M3() * ray.W();
	float vy = m.M4() * ray.X() + m.M5() * ray.Y() + m.M6() * ray.Z() + m.M7() * ray.W();
	float vz = m.M8() * ray.X() + m.M9() * ray.Y() + m.M10() * ray.Z() + m.M11() * ray.W();
	float vw = 1.0f;

	Vect worldRay = Vect(vx, vy, vz, vw);

	worldRay *= SceneManager::GetCurrentScene()->GetCamRotation();

	return worldRay;
}


