#ifndef _scenemanager
#define _scenemanager
#include "Updatable.h"
#include "SceneAttorney.h"
#include "NullScene.h"
#include "JsonHandler.h"
#include "SceneChangeCommand.h"

class SceneChangeCommandBase;
class SceneChangeNullCommand;
class Camera;

class SceneManager
{
	friend class SceneManagerAttorney;

public: // ---> USER METHODS

	/// <summary>
	/// Call this method to access the user methods of the current scene.
	/// </summary> 
	/// \ingroup VariousSceneMethods 
	static Scene* GetCurrentScene();

	/// <summary>
	/// Call this method to set the starting game scene. 
	/// 
	/// This should be called at the bottom of LoadAllResources.cpp
	/// </summary> 
	/// \ingroup VariousSceneMethods 
	template <typename scene>
	static void SetStartScene(Scene::EDITOR_ENABLED status)
	{
		delete SceneManager::Instance().m_ptrNullScene;
		SceneManager::Instance().m_currentScene = new scene; //scene HAS to be set before the editorStatus is called
		SceneAttorney::GameLoop::SetEditorStatus<scene>(SceneManager::Instance().m_currentScene, status);
	}

	/// <summary>
	/// Call this method to change the current scene to the input scene given.
	/// </summary> 
	/// \ingroup Camera 
	template <typename scene>
	static void SetNextScene(Scene* newScene)
	{
		assert(Instance().m_currentScene != newScene);

		JsonHandler::LoadData<scene>();

		Instance().m_sceneChangeCommand->SetScene(newScene);

		Instance().m_sceneChangeCheck = Instance().m_sceneChangeCommand;
	}

	/// <summary>
	/// Returns the 3D game camera of the current scene to be accessed.
	/// </summary> 
	/// \ingroup Camera 
	static Camera* Get3DCamera();

	/// <summary>
	/// Returns the 2D game camera of the current scene to be accessed.
	/// </summary> 
	/// \ingroup Camera 
	static Camera* Get2DCamera();

	/// <summary>
	/// Enables a free roam camera to be accessed by the user
	/// </summary> 
	/// \ingroup VariousSceneMethods 
	static void EnableGodCam();

	static void VisualizeAllCollisionVolumes();

private: // ---> ENGINE METHODS
	static void ChangeScene(Scene*);
	static void InitStartScene();
	static void Delete();
	static void Update();
	static void Draw();

private:
	SceneManager();
	SceneManager(const SceneManager&) = delete;
	SceneManager operator=(const SceneManager&) = delete;
	~SceneManager();

	static SceneManager& Instance()
	{
		if (!m_ptrInstance)
			m_ptrInstance = new SceneManager;
		return *m_ptrInstance;
	}

private:

	static SceneManager* m_ptrInstance;
	Scene* m_currentScene;
	NullScene* m_ptrNullScene;

	SceneChangeCommandBase* m_sceneChangeCheck;
	SceneChangeCommand* m_sceneChangeCommand;
	SceneChangeNullCommand* m_sceneChangeNullCommand;

};

#endif _scenemanager
#pragma once
