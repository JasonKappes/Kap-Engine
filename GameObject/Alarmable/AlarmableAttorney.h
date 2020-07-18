#ifndef _alarmableattorney
#define _alarmableattorney
#include "Alarmable.h"

class AlarmableAttorney
{
public:
	class GameLoop
	{
		friend class AlarmableManager;
	private:
		static void TriggerAlarm(Alarmable*, Alarm::ID);

	private:
		GameLoop() = delete;
		GameLoop(const GameLoop&) = delete;
		GameLoop operator=(const GameLoop&) = delete;
		~GameLoop() = delete;
	};

public:
	class Registration
	{
		friend class AlarmRegistrationCommand;
		friend class AlarmDeRegistrationCommand;
	private:
		static void SceneRegistration(Alarmable*, Alarm::ID, float);
		static void SceneDeRegistration(Alarmable*, Alarm::ID);
		static float GetAlarmTime(Alarmable*, Alarm::ID);

	private:
		Registration() = delete;
		Registration(const Registration&) = delete;
		Registration operator=(const Registration&) = delete;
		~Registration() = delete;
	};

private:
	AlarmableAttorney() = delete;
	AlarmableAttorney(const AlarmableAttorney&) = delete;
	AlarmableAttorney operator=(const AlarmableAttorney&) = delete;
	~AlarmableAttorney() = delete;
};

#endif _alarmableattorney
#pragma once
