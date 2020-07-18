#include "SceneManagerAttorney.h"

void SceneManagerAttorney::Base::Update()
{
	SceneManager::Update();
}

void SceneManagerAttorney::Base::Draw()
{
	SceneManager::Draw();
}

void SceneManagerAttorney::Base::Delete()
{
	SceneManager::Delete();
}

void SceneManagerAttorney::Base::InitStartScene()
{
	SceneManager::InitStartScene();
}

void SceneManagerAttorney::Change::ChangeScene(Scene* t_newScene)
{
	SceneManager::ChangeScene(t_newScene);
}
