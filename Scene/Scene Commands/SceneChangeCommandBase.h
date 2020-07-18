#ifndef _scenechangecommandbase
#define _scenechangecommandbase
#include "CommandBase.h"

class SceneChangeCommandBase : public CommandBase
{
public:
	SceneChangeCommandBase() = default;
	SceneChangeCommandBase(const SceneChangeCommandBase&) = delete;
	virtual ~SceneChangeCommandBase() {}
};

#endif _scenechangecommandbase
#pragma once
