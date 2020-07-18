#ifndef _scene
#define _scene
#include "Alarmable.h"
#include "AlarmableManager.h"
#include "DrawableManager.h"
#include "UpdatableManager.h"
#include "KeyboardEventManager.h"
#include "MouseEventManager.h"
#include "CameraManager.h"
#include "CollidableManager.h"
#include "SerializableManager.h"
#include "WorldEditorManager.h"
#include "SelectableManager.h"
#include "TerrainObjectManager.h"
#include "KapEngine.h"
#include "GameUpdate.h"
#include "EditorUpdate.h"
#include "EditorDraw.h"
#include "GameDraw.h"

class SceneRegistrationBroker;
class SceneRegistrationCommand;
class SystemUpdate;
class Touchable;
class Inputable;
class Camera;

class Scene
{
	friend class SceneAttorney;
public: // ----> USER Methods
	Scene();
	Scene(const Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	virtual ~Scene();

	/// <summary>
	/// Allows the player to set the position of the camera and set the position of the target for the camera to point towards.
	/// 
	/// Call this function at the start of the scene, although this can be called at anytime to point towards a new target.
	/// </summary> 
	/// \ingroup Camera
	void SetStartingCameraPosition(Vect cameraStartingPosition, Vect targetStartingPosition);

	/// <summary>
	/// Allows the player to move the camera in a desired direction based off of input.
	/// </summary> 
	/// \ingroup Camera
	void CamAddMovement(Vect offsetAmount);

	/// <summary>
	/// Allows the player to rotate the camera in a desired direction. These rotations happens based on world space (not local space)
	/// 
	/// The Matrix input has the desired amount of rotation.
	/// 
	/// Recommended syntax: CamLocalSpaceRotation( Matrix(Rot_Y, rotation_speed) );
	/// </summary> 
	/// \ingroup Camera
	void CamLocalSpaceRotation(Matrix localRotationAmount);

	Matrix& GetCamRotation();

	/// <summary>
	/// Allows the player to rotate the camera in a desired direction. These rotations happens based on local space
	/// 
	/// The Vector input is the desired amount of rotation and the float input is the desired speed of the rotation.
	/// 
	/// Recommended syntax: CanWorldSpaceRotation( Vect(...), CamRotSpeed );
	/// </summary> 
	/// \ingroup Camera
	void CamWorldSpaceRotation(Vect rotationDirection, float rotationSpeed);

	/// <summary>
	/// Takes the target's rotation and position and points towards the target
	/// 
	/// If this is called everyframe with the target's updated rotation and position, the camera will move and rotate with the player at the same viewing angle.
	/// 
	/// Set the initial viewing angle of the camera with SetStartingCameraPosition()
	/// </summary> 
	/// \ingroup Camera
	void CamLookAtTarget(Matrix TargetRotation, Vect TargetPosition);

	/// <summary>
	/// Takes the target's position and points towards the target
	/// 
	/// If this is called everyframe with the target's updated position, the camera will move with the player at the same viewing angle. It will not follow the player's rotation
	/// 
	/// Set the initial viewing angle of the camera with SetStartingCameraPosition()
	/// </summary> 
	/// \ingroup Camera
	void CamSimpleFollow(Vect targetPosition);

	void FirstPersonView(const Vect& targetPosition, float heightCameraOffset) const;

	/// <summary>
	/// GameObject De/Registration commands are sent to this method and executed the next frame.
	/// </summary> 
	/// \ingroup VariousSceneMethods
	void SubmitCommand(SceneRegistrationCommand*);

	/// <summary>
	/// Returns the current 3D game camera.
	/// </summary> 
	/// \ingroup VariousSceneMethods
	Camera* Get3DCamera();

	/// <summary>
	/// Returns the current 2D game camera.
	/// </summary> 
	/// \ingroup VariousSceneMethods
	Camera* Get2DCamera();

	void VisualizeCollisionVolumes() const;

	template <typename clickerobj>
	void FindMouseSelections(Touchable*);

	void Save();

	TerrainObject* GetTerrain();

public:
	enum class EDITOR_ENABLED
	{
		NO, YES
	};

protected: // ----> USER METHODS

	template <typename C1>
	void SetCollisionTerrain()
	{
		m_CollidableManager->SetCollisionTerrain<C1>();
	}

	/// <summary>
	/// If collision detection between two unique GameObject-derived classes is desired, they should be registered as a collision pair during Scene construction.
	/// 
	/// Recommended Syntax: SetCollisionPair<GameObjectClass1, GameObjectClass2>();
	/// </summary> 
	/// \ingroup Collidable
	template< typename C1, typename C2>
	void SetCollisionPair()
	{
		m_CollidableManager->SetCollisionPair<C1, C2>();
	}

	/// <summary>
	/// If collision detection between the same GameObject-derived class is desired, they should be registered as a collision self-pair during Scene construction.
	/// 
	/// Recommended Syntax: SetCollisionSelf<GameObjectClass1>();
	/// </summary> 
	/// \ingroup Collidable
	template< typename C1>
	void SetCollisionSelf()
	{
		m_CollidableManager->SetCollisionSelf<C1>();
	}

protected:
	void SetTerrain(const char* filename);


private: // ----> ENGINE METHODS, USER METHODS (to override)
	virtual void Initialize() = 0;
	virtual void SceneEnd() = 0;

private: // ----> ENGINE METHODS
	virtual void Register(Updatable*, UpdatableManager::StorageListRef&);
	virtual void Register(Drawable*, DrawableManager::StorageListRef&);
	virtual void Register(float, Alarmable*, Alarm::ID, Alarm::StorageEntryRef&);
	virtual void Register(Inputable*, AZUL_KEY, EVENT_TYPE, SingleKeyEventManager::KeyStorageRef&);
	virtual void Register(Touchable*, AZUL_MOUSE, MOUSE_EVENT_TYPE, SingleMouseEventManager::KeyStorageRef&);
	virtual void Register(Selectable*, SelectableManager::SelectableCollRef&);

	virtual void DeRegister(UpdatableManager::StorageListRef&);
	virtual void DeRegister(DrawableManager::StorageListRef&);
	virtual void DeRegister(Alarm::StorageEntryRef&);
	virtual void DeRegister(AZUL_KEY, EVENT_TYPE, SingleKeyEventManager::KeyStorageRef&);
	virtual void DeRegister(AZUL_MOUSE, MOUSE_EVENT_TYPE, SingleMouseEventManager::KeyStorageRef&);
	virtual void DeRegister(SelectableManager::SelectableCollRef&);

	void Draw();
	void Update();
	void SceneCleanUp();

	template <typename scene>
	void SetEditorStatus(EDITOR_ENABLED status)
	{
		//Sets update strategy pattern
		this->m_editorStatus = status;

		if (status == Scene::EDITOR_ENABLED::NO) //game
		{
			JsonHandler::LoadData<scene>();
			this->m_DrawSystem = this->m_gameDraw;
			this->m_UpdateSystem = this->m_gameUpdate;
		}
		else{ //editor
			JsonHandler::LoadData<scene>();

			m_WorldEditorManager = new WorldEditorManager(m_CameraManager);
			this->m_editorDraw = new EditorDraw(*m_SerializableManager, *m_WorldEditorManager);
			this->m_editorUpdate = new EditorUpdate(*m_KeyboardEventManager, *m_MouseEventManager);

			this->m_DrawSystem = this->m_editorDraw;
			this->m_UpdateSystem = this->m_editorUpdate;
			this->m_CameraManager->EnableGodCam();
		}
	}

protected:
	UpdatableManager* m_UpdatableManager;
	DrawableManager* m_DrawableManager;
	AlarmableManager* m_AlarmableManager;
	KeyboardEventManager* m_KeyboardEventManager;
	MouseEventManager* m_MouseEventManager;
	SceneRegistrationBroker* m_RegistrationBroker;
	CollidableManager* m_CollidableManager;
	CameraManager* m_CameraManager;
	SerializableManager* m_SerializableManager;
	WorldEditorManager* m_WorldEditorManager;
	SelectableManager* m_SelectableManager;
	TerrainObjectManager* m_TerrainObjectManager;

private:
	GameDraw* m_gameDraw;
	EditorDraw* m_editorDraw;
	GameUpdate* m_gameUpdate;
	EditorUpdate* m_editorUpdate;

	SystemUpdate* m_UpdateSystem;
	SystemUpdate* m_DrawSystem;
	Scene::EDITOR_ENABLED m_editorStatus;
};


#endif _scene
#pragma once
