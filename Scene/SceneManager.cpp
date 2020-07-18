#include "SceneManager.h"
#include "SceneChangeCommand.h"
#include "SceneChangeNullCommand.h"
#include <iostream>

SceneManager* SceneManager::m_ptrInstance = nullptr;

SceneManager::SceneManager() : m_currentScene(nullptr),
m_sceneChangeCommand(new SceneChangeCommand), m_sceneChangeNullCommand(new SceneChangeNullCommand)
{
    this->m_sceneChangeCheck = m_sceneChangeNullCommand;
    this->m_ptrNullScene = new NullScene();
    this->m_currentScene = this->m_ptrNullScene;
}

void SceneManager::InitStartScene() 
{ 
    SceneAttorney::GameLoop::Initialize(Instance().m_currentScene);
}

Scene* SceneManager::GetCurrentScene() { return Instance().m_currentScene; }

void SceneManager::Update() 
{ 
    Instance().m_sceneChangeCheck->Execute();  // either nothing or a scene change

    SceneAttorney::GameLoop::Update(Instance().m_currentScene);
}

void SceneManager::Draw()
{
    SceneAttorney::GameLoop::Draw(Instance().m_currentScene);
}

Camera* SceneManager::Get3DCamera() { return Instance().m_currentScene->Get3DCamera(); }

Camera* SceneManager::Get2DCamera() { return Instance().m_currentScene->Get2DCamera(); }

void SceneManager::EnableGodCam()
{
    SceneAttorney::GameLoop::EnableGodCam(Instance().m_currentScene);
}

void SceneManager::VisualizeAllCollisionVolumes()
{
    Instance().m_currentScene->VisualizeCollisionVolumes();
}

void SceneManager::ChangeScene(Scene* s)
{
    SceneAttorney::GameLoop::SceneCleanUp(Instance().m_currentScene);

    delete Instance().m_currentScene;

    Instance().m_currentScene = s;

    SceneAttorney::GameLoop::Initialize(Instance().m_currentScene);

    Instance().m_sceneChangeCheck = Instance().m_sceneChangeNullCommand;
}

void SceneManager::Delete()
{
    delete Instance().m_sceneChangeCommand;
    delete Instance().m_sceneChangeNullCommand;

    SceneAttorney::GameLoop::SceneCleanUp(Instance().m_currentScene);

	delete Instance().m_currentScene;
	delete Instance().m_ptrInstance;
}

SceneManager::~SceneManager() { DebugMsg::out(" \n SCENE MANAGER Destructor "); }

