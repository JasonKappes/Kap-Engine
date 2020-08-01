#ifndef _cameramanager
#define _cameramanager
#include "Camera.h"
#include <unordered_map>

class GodCam;

class CameraManager : public Align16
{
public: /// ---->  ENGINE METHODS
	CameraManager();
	CameraManager(const CameraManager&) = delete;
	CameraManager operator=(const CameraManager&) = delete;
	~CameraManager();
	
	Camera* Get3DCamera();
	Camera* Get2DCamera();
	
	void SetCameraStartingPosition(Vect cameraStartingPosition, Vect playerStartingPosition);

	void AddCameraMovement(Vect dir);
	void AddLocalSpaceRotation(Matrix rotation);
	void AddWorldSpaceRotation(Vect dir, float speed);
	
	void SnapToObject(Vect pos);
	void LookAtTarget(Matrix rot, Vect pos);
	void FirstPersonView(const Vect& position, float cameraHeightOffset);
	void SimpleFollow(Vect targetPosition);
	void DefaultTopdownView();
	
	Matrix& GetCamRotation();
	void SetCamRotation(Matrix rot);

	void EnableGodCam();
	void DisableGodCam();

private:
	void SetupFor3DCamera();
	void SetupFor2DCamera();

private:
	Camera* m_camera3D;
	Camera* m_camera2D;
	GodCam* godCam;
	
	Matrix m_camRot;
	Matrix m_camRot;
	Matrix m_cameraPosition;
	Matrix m_godCamRot;
	
	Vect m_camUp;
	Vect m_camDir;
	Vect m_Look;
	Vect m_playerPosition;
	Vect m_camPos;
	Vect m_godCamPos;

	Vect m_startingCamPos;
	Vect m_startingCamRot;

};

#endif _cameramanager
#pragma once
