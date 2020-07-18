#include "AlarmableManager.h"
#include "AlarmableAttorney.h"
#include <algorithm>
#include <AzulCore.h>
#include "TimeManager.h"

AlarmableManager::AlarmableManager()
{
	this->m_elapsedTime = 0.0f;
}

AlarmableManager::~AlarmableManager() 
{ 
	this->m_timeline.clear();
	DebugMsg::out("\n ALARMABLE MANAGER destructor: there are %d alarms ", this->m_timeline.size());
}

void AlarmableManager::ProcessAlarms()
{
	this->m_elapsedTime++;

	this->it = this->m_timeline.begin();

	while (this->it != this->m_timeline.end() && TimeManager::GetTime() > (*this->it).first)
	{
		AlarmableAttorney::GameLoop::TriggerAlarm((*this->it).second.first, (*this->it).second.second);
		this->m_timeline.erase(this->it++); //returns iterator following the last removed element	
	}
}

void AlarmableManager::Register(float t_time, Alarmable* t_alarmable, Alarm::ID t_alarmID, Alarm::StorageEntryRef& t_iterator)
{
	t_iterator = this->m_timeline.insert({ t_time, std::make_pair(t_alarmable, t_alarmID) });
}

void AlarmableManager::DeRegister(const Alarm::StorageEntryRef& t_iterator)
{
	this->m_timeline.erase(t_iterator);
	DebugMsg::out("\n Alarm DEREGISTERED, there are %d alarms ", this->m_timeline.size());
}
