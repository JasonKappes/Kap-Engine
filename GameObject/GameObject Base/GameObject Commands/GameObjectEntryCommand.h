#ifndef _gameobjectentrycommand
#define _gameobjectentrycommand
#include "SceneRegistrationCommand.h"

class GameObject;

class GameObjectEntryCommand : public SceneRegistrationCommand
{
public:
	GameObjectEntryCommand() = delete;
	GameObjectEntryCommand(GameObject*);
	GameObjectEntryCommand(const GameObjectEntryCommand&) = delete;
	GameObjectEntryCommand operator=(const GameObjectEntryCommand&) = delete;

protected:
	void Execute() override;

private:
	GameObject* m_gameObject;
};

#endif _gameobjectentrycommand
#pragma once
