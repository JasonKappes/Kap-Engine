#include "GameObjectAttorney.h"
#include "GameObject.h"

void GameObjectAttorney::Game::ConnectToScene(GameObject& t_go)
{
	t_go.ConnectToScene();
}

void GameObjectAttorney::Game::DisconnectFromScene(GameObject& t_go)
{
	t_go.DisconnectFromScene();
}

//void GameObjectAttorney::Data::LoadData(GameObject& t_go)
//{
//	t_go.LoadData();
//}
//
//void GameObjectAttorney::Data::SaveData(GameObject* t_go)
//{
//	DebugMsg::out("\n save data ");
//	t_go->SaveData();
//}
