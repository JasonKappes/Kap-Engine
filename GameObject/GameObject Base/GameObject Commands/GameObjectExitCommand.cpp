#include "GameObjectExitCommand.h"
#include "GameObjectAttorney.h"

GameObjectExitCommand::GameObjectExitCommand(GameObject* t_go)
{
	this->m_gameObject = t_go;
}

void GameObjectExitCommand::Execute()
{
	GameObjectAttorney::Game::DisconnectFromScene(*this->m_gameObject);
}
