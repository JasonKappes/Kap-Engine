#ifndef _scenemanagerattorney
#define _scenemanagerattorney
#include "SceneManager.h"

class Scene;

class SceneManagerAttorney
{

public:
	class Base
	{
		friend class KapEngine;
	private:
		template <typename scene>
		static void SetStartScene(Scene*)
		{
			SceneManager::SetStartScene<scene>(Scene::EDITOR_ENABLED::NO);
		}

		static void InitStartScene();

		static void Update();
		static void Draw();
		static void Delete();

	private:
		Base() = delete;
		Base(const Base&) = delete;
		Base operator=(const Base&) = delete;
		~Base() = delete;
	};

	class Change
	{
		friend class SceneChangeCommand;
	private:
		static void ChangeScene(Scene*);

	private:
		Change() = delete;
		Change(const Change&) = delete;
		Change operator=(const Change&) = delete;
		~Change() = delete;
	};

private:
	SceneManagerAttorney() = delete;
	SceneManagerAttorney(const SceneManagerAttorney&) = delete;
	SceneManagerAttorney operator=(const SceneManagerAttorney&) = delete;
	~SceneManagerAttorney() = delete;
};

#endif _scenemanagerattorney
#pragma once
