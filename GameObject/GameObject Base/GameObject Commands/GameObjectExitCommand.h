#ifndef _gameobjectexitcommand
#define _gameobjectexitcommand
#include "SceneRegistrationCommand.h"

class GameObject;

class GameObjectExitCommand : public SceneRegistrationCommand
{
public:
	GameObjectExitCommand() = delete;
	GameObjectExitCommand(GameObject*);
	GameObjectExitCommand(const GameObjectExitCommand&) = delete;
	GameObjectExitCommand operator=(const GameObjectExitCommand&) = delete;

protected:
	void Execute() override;

private:
	GameObject* m_gameObject;
};

#endif _gameobjectexitcommand
#pragma once
