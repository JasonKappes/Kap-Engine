#ifndef _gameobjectattorney
#define _gameobjectattorney

class GameObject;

class GameObjectAttorney
{
public:
	class Game
	{
		friend class GameObjectEntryCommand;
		friend class GameObjectExitCommand;
	private:
		static void ConnectToScene(GameObject&);
		static void DisconnectFromScene(GameObject&);

	private:
		Game() = delete;
		Game(const Game&) = delete;
		Game operator=(const Game&) = delete;
		~Game() = delete;
	};

	/*class Data
	{
		friend class SerializableManager;
	private:
		static void LoadData(GameObject&);
		static void SaveData(GameObject*);

	private:
		Data() = delete;
		Data(const Data&) = delete;
		Data operator=(const Data&) = delete;
		~Data() = delete;
	};*/


private:
	GameObjectAttorney() = delete;
	GameObjectAttorney(const GameObjectAttorney&) = delete;
	GameObjectAttorney operator=(const GameObjectAttorney&) = delete;
	~GameObjectAttorney() = delete;
};

#endif _gameobjectattorney
#pragma once
