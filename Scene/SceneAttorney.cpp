#include "SceneAttorney.h"
#include "Scene.h"
#include "SceneManager.h"

void SceneAttorney::Registration::Register(Scene* t_scene, Updatable* t_updatable, UpdatableManager::StorageListRef& t_iterator)
{
	t_scene->m_UpdatableManager->Register(t_updatable, t_iterator);
}

void SceneAttorney::Registration::Register(Scene* t_scene, Drawable* t_drawable, DrawableManager::StorageListRef& t_iterator)
{
	t_scene->m_DrawableManager->Register(t_drawable, t_iterator);
}

void SceneAttorney::Registration::Register(Scene* t_scene, float t_time, Alarmable* t_alarmable, Alarm::ID t_alarmID, Alarm::StorageEntryRef& t_iterator)
{
	t_scene->m_AlarmableManager->Register(t_time, t_alarmable, t_alarmID, t_iterator);
}

void SceneAttorney::Registration::Register(Scene* t_scene, Inputable* t_inputable, AZUL_KEY t_key, EVENT_TYPE t_event, SingleKeyEventManager::KeyStorageRef& t_iterator)
{
	t_scene->m_KeyboardEventManager->RegisterSingleKey(t_inputable, t_key, t_event, t_iterator);
}

void SceneAttorney::Registration::Register(Scene* t_scene, Touchable* t_touchable, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event, SingleMouseEventManager::KeyStorageRef& t_iterator)
{
	t_scene->m_MouseEventManager->RegisterSingleMouseAction(t_touchable, t_key, t_event, t_iterator);
}

void SceneAttorney::Registration::DeRegister(Scene* t_scene, UpdatableManager::StorageListRef& t_iterator)
{
	t_scene->m_UpdatableManager->Deregister(t_iterator);
}

void SceneAttorney::Registration::DeRegister(Scene* t_scene, DrawableManager::StorageListRef& t_iterator)
{
	t_scene->m_DrawableManager->Deregister(t_iterator);
}

void SceneAttorney::Registration::DeRegister(Scene* t_scene, Alarm::StorageEntryRef& t_iterator)
{
	t_scene->m_AlarmableManager->DeRegister(t_iterator);
}

void SceneAttorney::Registration::DeRegister(Scene* t_scene, AZUL_KEY t_key, EVENT_TYPE t_event, SingleKeyEventManager::KeyStorageRef& t_delRef)
{
	t_scene->m_KeyboardEventManager->DeRegisterSingleKey(t_key, t_event, t_delRef);
}

void SceneAttorney::Registration::DeRegister(Scene* t_scene, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event, SingleMouseEventManager::KeyStorageRef& t_delRef)
{
	t_scene->m_MouseEventManager->DeRegisterSingleMouseAction(t_key, t_event, t_delRef);
}

UpdatableManager* SceneAttorney::Registration::GetUpdateMgr()
{
	return (SceneManager::GetCurrentScene()->m_UpdatableManager);
}

DrawableManager* SceneAttorney::Registration::GetDrawMgr()
{
	return (SceneManager::GetCurrentScene()->m_DrawableManager);
}

AlarmableManager* SceneAttorney::Registration::GetAlarmMgr()
{
	return SceneManager::GetCurrentScene()->m_AlarmableManager;
}

KeyboardEventManager* SceneAttorney::Registration::GetInputMgr()
{
	return (SceneManager::GetCurrentScene()->m_KeyboardEventManager);
}

CollidableManager* SceneAttorney::Registration::GetCollidableMgr()
{
	return SceneManager::GetCurrentScene()->m_CollidableManager;
}

SerializableManager* SceneAttorney::Registration::GetSerializableMgr()
{
	return SceneManager::GetCurrentScene()->m_SerializableManager;
}

SelectableManager* SceneAttorney::Registration::GetSelectableManager()
{
	return SceneManager::GetCurrentScene()->m_SelectableManager;
}

MouseEventManager* SceneAttorney::Registration::GetTouchMgr()
{
	return (SceneManager::GetCurrentScene()->m_MouseEventManager);
}

CameraManager* SceneAttorney::Registration::GetCameraManager()
{
	return (SceneManager::GetCurrentScene()->m_CameraManager);
}

TerrainObjectManager* SceneAttorney::Registration::GetTerrainObjectManager()
{
	return SceneManager::GetCurrentScene()->m_TerrainObjectManager;
}

void SceneAttorney::GameLoop::Update(Scene* t_currScene)
{
	t_currScene->Update();
}

void SceneAttorney::GameLoop::Draw(Scene* t_currScene)
{
	t_currScene->Draw();
}

void SceneAttorney::GameLoop::EnableGodCam(Scene* t_currScene)
{
	t_currScene->m_CameraManager->EnableGodCam();
}

void SceneAttorney::GameLoop::Initialize(Scene* t_currScene)
{
	t_currScene->Initialize();
}

void SceneAttorney::GameLoop::SceneCleanUp(Scene* t_currScene)
{
	t_currScene->SceneCleanUp();
}
