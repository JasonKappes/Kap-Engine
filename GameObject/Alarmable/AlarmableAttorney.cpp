#include "AlarmableAttorney.h"
//
//void AlarmableAttorney::GameLoop::TriggerAlarm(Alarmable* t_alarmable, Alarm::ID t_alarmID) { t_alarmable->TriggerAlarm(t_alarmID); }

void AlarmableAttorney::Registration::SceneRegistration(Alarmable* t_alarmable, Alarm::ID t_alarmID, float t_time) 
{ 
	t_alarmable->AlarmRegistration(t_alarmID, t_time); 
}

void AlarmableAttorney::Registration::SceneDeRegistration(Alarmable* t_alarmable, Alarm::ID t_alarmID) 
{ 
	t_alarmable->AlarmDeRegistration(t_alarmID); 
}

float AlarmableAttorney::Registration::GetAlarmTime(Alarmable* t_alarmable, Alarm::ID t_alarmID)
{
	return t_alarmable->GetAlarmTime(t_alarmID);
}

void AlarmableAttorney::GameLoop::TriggerAlarm(Alarmable* t_alarmable, Alarm::ID t_alarmID)
{
	t_alarmable->TriggerAlarm(t_alarmID);
}
