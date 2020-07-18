#include "Scene.h"
#include "SceneRegistrationBroker.h"
#include "SceneRegistrationCommand.h"
#include <chrono>
#include <iostream>
#include <fstream>
#include "json.h"


Scene::Scene()
{
	this->m_DrawableManager			= new DrawableManager(); //initiate before gameobjects
	this->m_UpdatableManager		= new UpdatableManager(); //initiate before gameobjects
	this->m_AlarmableManager		= new AlarmableManager(); //initiate before gameobjects
	this->m_RegistrationBroker		= new SceneRegistrationBroker(); //initiate before gameobjects
	this->m_KeyboardEventManager	= new KeyboardEventManager(); //initiate before gameobjects
	this->m_CollidableManager		= new CollidableManager(); //initiate before gameobjects
	this->m_CameraManager			= new CameraManager(); //initiate before gameobjects
	this->m_SerializableManager		= new SerializableManager();
	this->m_MouseEventManager		= new MouseEventManager();
	this->m_SelectableManager		= new SelectableManager();
	this->m_TerrainObjectManager	= new TerrainObjectManager();

	this->m_gameDraw = new GameDraw(*m_DrawableManager);
	this->m_gameUpdate = new GameUpdate(*m_KeyboardEventManager, m_RegistrationBroker, *m_UpdatableManager, *m_CollidableManager, m_AlarmableManager, *m_MouseEventManager);

	//default settings, changed otherwise if editor is enabled
	this->m_UpdateSystem = m_gameUpdate;
	this->m_DrawSystem = m_gameDraw;

}

void Scene::Update()
{
	this->m_UpdateSystem->Tick();
}

void Scene::Draw()
{
	this->m_DrawSystem->Tick();
}

void Scene::Save()
{
	JsonHandler::CreateBackupSave();
	this->m_SerializableManager->WriteSerializables();
}

void Scene::VisualizeCollisionVolumes() const
{
	this->m_CollidableManager->VisualizeAllVolumes();
}

TerrainObject* Scene::GetTerrain()
{
	assert(this->m_TerrainObjectManager->GetTerrainObject() != nullptr);

	return this->m_TerrainObjectManager->GetTerrainObject();
}

void Scene::SetTerrain(const char* filename)
{
	this->m_TerrainObjectManager->EnableTerrain(filename);
}

void Scene::SubmitCommand(SceneRegistrationCommand* t_command)
{
	this->m_RegistrationBroker->AddCommand(t_command);
}

void Scene::Register(Updatable* t_updatable, UpdatableManager::StorageListRef& t_iterator)
{
	this->m_UpdatableManager->Register(t_updatable, t_iterator);
}

void Scene::Register(Drawable* t_drawable, DrawableManager::StorageListRef& t_iterator)
{
	this->m_DrawableManager->Register(t_drawable, t_iterator);
}

void Scene::Register(float t_time, Alarmable* t_alarmable, Alarm::ID t_alarmID, Alarm::StorageEntryRef& t_iterator)
{
	this->m_AlarmableManager->Register(t_time, t_alarmable, t_alarmID, t_iterator);
}

void Scene::Register(Inputable* t_inputable, AZUL_KEY t_key, EVENT_TYPE t_event, SingleKeyEventManager::KeyStorageRef& t_iterator)
{
	this->m_KeyboardEventManager->RegisterSingleKey(t_inputable, t_key, t_event, t_iterator);
}

void Scene::Register(Touchable* t_touchable, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event, SingleMouseEventManager::KeyStorageRef& t_iterator)
{
	this->m_MouseEventManager->RegisterSingleMouseAction(t_touchable, t_key, t_event, t_iterator);
}

void Scene::Register(Selectable* t_selectable, SelectableManager::SelectableCollRef& t_iterator)
{
	this->m_SelectableManager->Register(t_selectable, t_iterator);
}

void Scene::DeRegister(UpdatableManager::StorageListRef& t_iterator)
{
	this->m_UpdatableManager->Deregister(t_iterator);
}

void Scene::DeRegister(DrawableManager::StorageListRef& t_iterator)
{
	this->m_DrawableManager->Deregister(t_iterator);
}

void Scene::DeRegister(Alarm::StorageEntryRef& t_iterator)
{
	this->m_AlarmableManager->DeRegister(t_iterator);
}

void Scene::DeRegister(AZUL_KEY t_key, EVENT_TYPE t_event, SingleKeyEventManager::KeyStorageRef& t_delRef)
{
	this->m_KeyboardEventManager->DeRegisterSingleKey(t_key, t_event, t_delRef);
}

void Scene::DeRegister(AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event, SingleMouseEventManager::KeyStorageRef& t_delRef)
{
	this->m_MouseEventManager->DeRegisterSingleMouseAction(t_key, t_event, t_delRef);
}

void Scene::DeRegister(SelectableManager::SelectableCollRef& t_iterator)
{
	this->m_SelectableManager->Deregister(t_iterator);
}

Camera* Scene::Get3DCamera() { return this->m_CameraManager->Get3DCamera(); }

Camera* Scene::Get2DCamera() { return this->m_CameraManager->Get2DCamera(); }

template <typename clickerobj>
void Scene::FindMouseSelections(Touchable* t_touchable)
{
	this->m_SelectableManager->ProcessSelections<clickerobj>(t_touchable);
}

void Scene::CamAddMovement(Vect offset)
{
	this->m_CameraManager->AddCameraMovement(offset);
}

void Scene::CamLocalSpaceRotation(Matrix rotation)
{
	this->m_CameraManager->AddLocalSpaceRotation(rotation);
}

void Scene::CamWorldSpaceRotation(Vect dir, float speed)
{
	this->m_CameraManager->AddWorldSpaceRotation(dir, speed);
}

void Scene::CamLookAtTarget(Matrix rot, Vect pos)
{
	this->m_CameraManager->LookAtTarget(rot, pos);
}

void Scene::FirstPersonView(const Vect& pos, float cameraHeightOffset) const
{
	this->m_CameraManager->FirstPersonView(pos, cameraHeightOffset);
}

void Scene::CamSimpleFollow(Vect targetPosition)
{
	this->m_CameraManager->SimpleFollow(targetPosition);
}

void Scene::SetStartingCameraPosition(Vect cameraStartingPosition, Vect targetStartingPosition)
{
	this->m_CameraManager->SetCameraStartingPosition(cameraStartingPosition, targetStartingPosition);
}

Matrix& Scene::GetCamRotation()
{
	return this->m_CameraManager->GetCamRotation();
}

void Scene::SceneCleanUp()
{
	if (m_editorStatus == Scene::EDITOR_ENABLED::YES)
	{
		Save();
	}
	SceneEnd(); //User overriden
}

Scene::~Scene()
{
	if (this->m_editorStatus == Scene::EDITOR_ENABLED::YES)
	{
		delete this->m_editorDraw;
		delete this->m_editorUpdate;
		delete this->m_WorldEditorManager;
	}

	delete this->m_gameDraw;
	delete this->m_gameUpdate;
	delete this->m_DrawableManager;
	delete this->m_UpdatableManager;
	delete this->m_AlarmableManager;
	delete this->m_RegistrationBroker;
	delete this->m_KeyboardEventManager;
	delete this->m_CollidableManager;
	delete this->m_CameraManager;
	delete this->m_SerializableManager;
	delete this->m_MouseEventManager;
	delete this->m_SelectableManager;
	delete this->m_TerrainObjectManager;
}
