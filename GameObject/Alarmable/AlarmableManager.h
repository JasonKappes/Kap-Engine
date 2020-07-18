#ifndef _alarmablemanager
#define _alarmablemanager
#include "AlarmID.h"
#include <map>

class Alarmable;

class AlarmableManager
{
public:
	AlarmableManager();
	AlarmableManager(const AlarmableManager&) = delete;
	AlarmableManager operator=(const AlarmableManager&) = delete;
	~AlarmableManager();

	void ProcessAlarms();
	void Register(float, Alarmable*, Alarm::ID, Alarm::StorageEntryRef&);
	void DeRegister(const Alarm::StorageEntryRef&);

public:
	float m_elapsedTime;

private:
	Alarm::TimeLineMap m_timeline;
	Alarm::StorageEntryRef it;

};

#endif _alarmablemanager
#pragma once
