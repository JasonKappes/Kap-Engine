#ifndef _scenechangecommand
#define _scenechangecommand
#include "SceneChangeCommandBase.h"

class Scene;

class SceneChangeCommand : public SceneChangeCommandBase
{
public:
	SceneChangeCommand();
	SceneChangeCommand(const SceneChangeCommand&) = delete;
	SceneChangeCommand operator=(const SceneChangeCommand&) = delete;
	~SceneChangeCommand() = default;

	void SetScene(Scene*);
	void Execute() override;

private:
	Scene* m_scene;
};


#endif _scenechangecommand
#pragma once
