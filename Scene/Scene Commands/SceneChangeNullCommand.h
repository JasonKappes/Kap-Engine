#ifndef _scenechangenullcommand
#define _scenechangenullcommand
#include "SceneChangeCommandBase.h"

class Scene;

class SceneChangeNullCommand : public SceneChangeCommandBase
{
public:
	SceneChangeNullCommand();
	SceneChangeNullCommand(const SceneChangeNullCommand&) = delete;
	SceneChangeNullCommand operator=(const SceneChangeNullCommand&) = delete;
	~SceneChangeNullCommand() = default;
	void Execute() override;

};


#endif _scenechangenullcommand
#pragma once
