#ifndef _alarmregistrationcommand
#define _alarmregistrationcommand
#include "SceneRegistrationCommand.h"
#include "AlarmableManager.h"

class Alarmable;

class AlarmRegistrationCommand : public SceneRegistrationCommand
{
public:
	AlarmRegistrationCommand() = delete;
	AlarmRegistrationCommand(Alarmable*, Alarm::ID);
	AlarmRegistrationCommand(const AlarmRegistrationCommand&) = delete;
	AlarmRegistrationCommand operator=(const AlarmRegistrationCommand&) = delete;
	~AlarmRegistrationCommand() = default;

protected:
	void Execute() override;

private:
	Alarmable* m_ptrAlarmable;
	Alarm::ID m_alarmID;
	float m_alarmTime;
};

#endif _alarmregistrationcommand
#pragma once
