#include "AlarmRegistrationCommand.h"
#include "AlarmableAttorney.h"
#include "Alarmable.h"

AlarmRegistrationCommand::AlarmRegistrationCommand(Alarmable* t_ptrAlarmable, Alarm::ID t_alarm)
{
	this->m_ptrAlarmable = t_ptrAlarmable;
	this->m_alarmID = t_alarm;
}

void AlarmRegistrationCommand::Execute()
{
	AlarmableAttorney::Registration::SceneRegistration(this->m_ptrAlarmable, this->m_alarmID,  
		AlarmableAttorney::Registration::GetAlarmTime(this->m_ptrAlarmable, this->m_alarmID));
}
