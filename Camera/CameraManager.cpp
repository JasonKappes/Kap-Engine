#include "CameraManager.h"
#include "KapEngine.h"
#include "GodCam.h"

CameraManager::CameraManager()
{
	SetupFor2DCamera();
	SetupFor3DCamera();
	this->m_camera2D->updateCamera();
	godCam = new GodCam();
}

void CameraManager::SetCameraStartingPosition(Vect t_startingPosition, Vect t_playerPosition)
{
	this->m_playerPosition = t_playerPosition;
	this->m_startingCamPos = t_startingPosition;
	this->m_camPos = this->m_startingCamPos;
	
	this->m_camRot.set(ROT_ORIENT, m_startingCamRot - this->m_camPos, this->m_camUp);
	this->m_camera3D->setOrientAndPosition(this->m_camUp * this->m_camRot, this->m_camPos + this->m_camDir * this->m_camRot, this->m_camPos);
	this->m_camera3D->updateCamera();
}

Camera* CameraManager::Get3DCamera()
{
	return this->m_camera3D;
}

Camera* CameraManager::Get2DCamera()
{
	return this->m_camera2D;
}

void CameraManager::AddCameraMovement(Vect t_camOffset)
{
	this->m_camPos += t_camOffset * m_camRot;

	this->m_camera3D->setOrientAndPosition(m_camUp * m_camRot, m_camPos + m_camDir * m_camRot, m_camPos);

	this->m_camera3D->updateCamera();
}

void CameraManager::AddLocalSpaceRotation(Matrix rotation)
{
	this->m_camRot *= rotation;

	this->m_camera3D->setOrientAndPosition(m_camUp * m_camRot, m_camPos + m_camDir * m_camRot, m_camPos);

	this->m_camera3D->updateCamera();
}

void CameraManager::AddWorldSpaceRotation(Vect dir, float speed)
{
	this->m_camRot *= Matrix(ROT_AXIS_ANGLE, dir * this->m_camRot, speed);

	this->m_camera3D->setOrientAndPosition(m_camUp * m_camRot, m_camPos + m_camDir * m_camRot, m_camPos);

	this->m_camera3D->updateCamera();
}

void CameraManager::DefaultTopdownView()
{

	//default starting position
	SetCameraStartingPosition(Vect(0, 2000.0f, 500.0f), Vect(0, 0, 0));

	this->m_camera3D->setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0), this->m_camPos);

	this->m_camera3D->updateCamera();
}

void CameraManager::EnableGodCam()
{
	if(!godCam->isEnabled())	godCam->SceneEntry();
}

void CameraManager::DisableGodCam()
{
	if(godCam->isEnabled()) godCam->SceneExit();
}

void CameraManager::SetCamRotation(Matrix rot)
{
	this->m_camRot = rot;
}

void CameraManager::SnapToObject(Vect obj)
{
	float heightAboveObject = 1000.0f;
	float additionalZoffset = 0.0f;
	this->m_playerPosition = Vect(obj.X(), obj.Y() + heightAboveObject, obj.Z() + additionalZoffset);
	SimpleFollow(this->m_playerPosition);
}


void CameraManager::FirstPersonView(const Vect& t_shipPos, float cameraHeightOffset)
{
	this->m_camPos = t_shipPos + Vect(0, cameraHeightOffset + 10.0f, -5.0f);

	this->m_camera3D->setOrientAndPosition(m_camUp * m_camRot, m_camPos + m_camDir * m_camRot, m_camPos);

	this->m_camera3D->updateCamera();
}

void CameraManager::LookAtTarget(Matrix t_rotation, Vect t_ShipPos)
{
	this->m_camRot *= t_rotation;

	this->m_playerPosition = t_ShipPos;

	Matrix ShipRotPos = this->m_camRot * Matrix(TRANS, this->m_playerPosition);  // This is the worldmat without scaling

	this->m_camPos = this->m_startingCamPos * ShipRotPos;

	this->m_camera3D->setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0) * ShipRotPos, this->m_camPos);

	this->m_camera3D->updateCamera();
}

void CameraManager::SimpleFollow(Vect ShipPosition)
{
	this->m_playerPosition = ShipPosition;

	Matrix ShipRotPos = Matrix(TRANS, this->m_playerPosition);  // This is the worldmat without scaling

	this->m_camPos = this->m_startingCamPos * ShipRotPos;

	this->m_camRot = Matrix(IDENTITY);		// No rotation initially
	this->m_camUp = Vect(0, 1, 0);			// Using local Y axis as 'Up'
	this->m_camDir = Vect(0, 0, 1);
	Vect tmpCamPos = Vect(0.0f, m_camPos.Y(), m_camPos.Z(), m_camPos.W());
	this->m_camRot.set(ROT_ORIENT, m_startingCamRot - tmpCamPos, this->m_camUp);

	this->m_camera3D->setOrientAndPosition(Vect(0, 1, 0), Vect(0, 0, 0) * ShipRotPos, this->m_camPos);

	this->m_camera3D->updateCamera();
}

void CameraManager::SetupFor3DCamera()
{
	this->m_camera3D = new Camera(Camera::Type::PERSPECTIVE_3D);

	this->m_camera3D->setViewport(0, 0, KapEngine::GetWindowWidth(), KapEngine::GetWindowHeight());
	this->m_camera3D->setPerspective(35.0f, float(KapEngine::GetWindowWidth()) / float(KapEngine::GetWindowHeight()), 1.0f, 500000.0f);

	this->m_startingCamPos = Vect(0, 0, 0.0f);
	this->m_startingCamRot = Vect(0, 0, 0);

	this->m_Look = Vect(0, -100.0f, 0.0f);
	this->m_camPos = this->m_startingCamPos;
	this->m_camRot = Matrix(IDENTITY);		// No rotation initially
	this->m_camUp = Vect(0, 1, 0);			// Using local Y axis as 'Up'
	this->m_camDir = Vect(0, 0, 1);
	this->m_camRot.set(ROT_ORIENT, m_startingCamRot - this->m_camPos, this->m_camUp);

	this->m_camera3D->setOrientAndPosition(this->m_camUp * this->m_camRot, this->m_camPos + this->m_camDir * this->m_camRot, this->m_camPos);

	SetCameraStartingPosition(Vect(0, 2000.0f, 500.0f), Vect(0, 0, 0));
}

void CameraManager::SetupFor2DCamera()
{
	this->m_camera2D = new Camera(Camera::Type::ORTHOGRAPHIC_2D);

	this->m_camera2D->setViewport(0, 0, KapEngine::GetWindowWidth(), KapEngine::GetWindowHeight());
	this->m_camera2D->setOrthographic(-0.5f * KapEngine::GetWindowWidth(), 0.5f * KapEngine::GetWindowWidth(), -0.5f * KapEngine::GetWindowHeight(), 0.5f * KapEngine::GetWindowHeight(), 1.0f, 1000.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	this->m_camera2D->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);
}

Matrix& CameraManager::GetCamRotation()
{
	return this->m_camRot;
}

CameraManager::~CameraManager()
{
	delete this->m_camera3D;
	delete this->m_camera2D;
	delete this->godCam;
}
