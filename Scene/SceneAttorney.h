#ifndef _sceneattorney
#define _sceneattorney
#include "Scene.h"

class SceneRegistrationCommand;
class EditorInput;

class SceneAttorney
{

public:
	class Registration
	{
		friend class Alarmable;
		friend class Updatable;
		friend class Drawable;
		friend class Inputable;
		friend class Collidable;
		friend class Serializable;
		friend class Touchable;
		friend class Selectable;
		friend class EditorInput;
		friend class ActiveObject;
		friend class ReviveSerializableCommand;
	private:
		void Register(Scene*, Updatable*, UpdatableManager::StorageListRef&);
		void Register(Scene*, Drawable*, DrawableManager::StorageListRef&);
		void Register(Scene*, float, Alarmable*, Alarm::ID, Alarm::StorageEntryRef&);
		void Register(Scene*, Inputable*, AZUL_KEY, EVENT_TYPE, SingleKeyEventManager::KeyStorageRef&);
		void Register(Scene*, Touchable*, AZUL_MOUSE, MOUSE_EVENT_TYPE, SingleMouseEventManager::KeyStorageRef&);

		void DeRegister(Scene*, UpdatableManager::StorageListRef&);
		void DeRegister(Scene*, DrawableManager::StorageListRef&);
		void DeRegister(Scene*, Alarm::StorageEntryRef&);
		void DeRegister(Scene*, AZUL_KEY, EVENT_TYPE, SingleKeyEventManager::KeyStorageRef&);
		void DeRegister(Scene*, AZUL_MOUSE, MOUSE_EVENT_TYPE, SingleMouseEventManager::KeyStorageRef&);

		static UpdatableManager*		GetUpdateMgr();
		static DrawableManager*			GetDrawMgr();
		static AlarmableManager*		GetAlarmMgr();
		static KeyboardEventManager*	GetInputMgr();
		static CollidableManager*		GetCollidableMgr();
		static SerializableManager*		GetSerializableMgr();
		static MouseEventManager*		GetTouchMgr();
		static CameraManager*			GetCameraManager();
		static SelectableManager*		GetSelectableManager();
		static TerrainObjectManager*	GetTerrainObjectManager();
	};

	class GameLoop
	{
		friend class SceneManager;
	private:
		static void Update(Scene*);
		static void Draw(Scene*);
		static void Initialize(Scene*);
		static void SceneCleanUp(Scene*);
		static void EnableGodCam(Scene*);

		template <typename scene>
		static void SetEditorStatus(Scene* t_currScene, Scene::EDITOR_ENABLED t_status)
		{
			t_currScene->SetEditorStatus<scene>(t_status);
		}
	};



private:
	SceneAttorney() = delete;
	SceneAttorney(const SceneAttorney&) = delete;
	SceneAttorney operator=(const SceneAttorney&) = delete;
	~SceneAttorney() = delete;
};

#endif _sceneattorney
#pragma once
