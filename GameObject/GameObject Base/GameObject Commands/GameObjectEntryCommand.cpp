#include "GameObjectAttorney.h"
#include "GameObjectEntryCommand.h"

GameObjectEntryCommand::GameObjectEntryCommand(GameObject* t_gameobject)
{
	this->m_gameObject = t_gameobject;
}

void GameObjectEntryCommand::Execute()
{
	GameObjectAttorney::Game::ConnectToScene(*this->m_gameObject);
}
