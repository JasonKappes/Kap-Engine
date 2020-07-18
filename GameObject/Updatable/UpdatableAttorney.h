#ifndef _updatableattorney
#define _updatableattorney

class Updatable;

class UpdatableAttorney
{
public:
	class GameLoop
	{
		friend class UpdatableManager;
	private:
		static void Update(Updatable*);
		static void LateUpdate(Updatable*);

	private:
		GameLoop() = delete;
		GameLoop(const GameLoop&) = delete;
		GameLoop operator=(const GameLoop&) = delete;
		~GameLoop() = delete;
	};

public:
	class Registration
	{
		friend class UpdateRegistrationCommand;
		friend class UpdateDeRegistrationCommand;
	private:
		static void SceneRegistration(Updatable*);
		static void SceneDeRegistration(Updatable*);

	private:
		Registration() = delete;
		Registration(const Registration&) = delete;
		Registration operator=(const Registration&) = delete;
		~Registration() = delete;
	};

private:
	UpdatableAttorney() = delete;
	UpdatableAttorney(const UpdatableAttorney&) = delete;
	UpdatableAttorney operator=(const UpdatableAttorney&) = delete;
	~UpdatableAttorney() = delete;
};

#endif _updatableattorney
#pragma once
