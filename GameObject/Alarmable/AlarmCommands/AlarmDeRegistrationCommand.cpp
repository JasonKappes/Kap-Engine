#include "AlarmDeRegistrationCommand.h"
#include "AlarmableAttorney.h"
#include "Alarmable.h"

AlarmDeRegistrationCommand::AlarmDeRegistrationCommand(Alarmable* t_ptrAlarmable, Alarm::ID t_alarmID)
{
	this->m_ptrAlarmable = t_ptrAlarmable;
	this->m_alarmID = t_alarmID;
}

void AlarmDeRegistrationCommand::Execute()
{
	AlarmableAttorney::Registration::SceneDeRegistration(this->m_ptrAlarmable, this->m_alarmID);
}
