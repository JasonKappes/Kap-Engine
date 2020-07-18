#ifndef _alarmderegistrationcommand
#define _alarmderegistrationcommand
#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmDeRegistrationCommand : public SceneRegistrationCommand
{
public:
	AlarmDeRegistrationCommand() = delete;
	AlarmDeRegistrationCommand(Alarmable*, Alarm::ID);
	AlarmDeRegistrationCommand(const AlarmDeRegistrationCommand&) = delete;
	AlarmDeRegistrationCommand operator=(const AlarmDeRegistrationCommand&) = delete;
	~AlarmDeRegistrationCommand() = default;

protected:
	void Execute() override;

private:
	Alarmable* m_ptrAlarmable;
	Alarm::ID m_alarmID;
	float m_alarmTime;
};

#endif _alarmderegistrationcommand
#pragma once
