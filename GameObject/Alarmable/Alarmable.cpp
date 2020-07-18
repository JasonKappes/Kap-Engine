#include "Alarmable.h"
#include "AlarmableManager.h"
#include "SceneAttorney.h"
#include "TimeManager.h"
#include "Scene.h"
#include "AlarmRegistrationCommand.h"
#include "AlarmDeRegistrationCommand.h"
#include "SceneManager.h"

Alarmable::Alarmable()
{
		this->RegData[0].m_alarmRegistrationCommand = new AlarmRegistrationCommand(this, Alarm::ID::_0);
		this->RegData[1].m_alarmRegistrationCommand = new AlarmRegistrationCommand(this, Alarm::ID::_1);
		this->RegData[2].m_alarmRegistrationCommand = new AlarmRegistrationCommand(this, Alarm::ID::_2);

		this->RegData[0].m_alarmDeRegistrationCommand = new AlarmDeRegistrationCommand(this, Alarm::ID::_0);
		this->RegData[1].m_alarmDeRegistrationCommand = new AlarmDeRegistrationCommand(this, Alarm::ID::_1);
		this->RegData[2].m_alarmDeRegistrationCommand = new AlarmDeRegistrationCommand(this, Alarm::ID::_2);

		this->RegData[0].m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		this->RegData[1].m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		this->RegData[2].m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
}

Alarmable::~Alarmable()
{
	delete this->RegData[0].m_alarmRegistrationCommand;
	delete this->RegData[0].m_alarmDeRegistrationCommand;

	delete this->RegData[1].m_alarmRegistrationCommand;
	delete this->RegData[1].m_alarmDeRegistrationCommand;

	delete this->RegData[2].m_alarmRegistrationCommand;
	delete this->RegData[2].m_alarmDeRegistrationCommand;
}

void Alarmable::TriggerAlarm(Alarm::ID id)
{
	switch (id)
	{
	case Alarm::ID::_0:
		this->RegData[0].m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		this->Alarm0();
		break;
	case Alarm::ID::_1:
		this->RegData[1].m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		this->Alarm1();
		break;
	case Alarm::ID::_2:
		this->RegData[2].m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		this->Alarm2();
		break;
	};	
}

void Alarmable::AlarmRegistration(Alarm::ID t_alarmID, float t_time)
{
	assert(this->RegData[t_alarmID].m_registrationState != RegistrationState::CURRENTLY_REGISTERED);

	this->RegData[t_alarmID].m_registrationState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Registration::GetAlarmMgr()->Register(TimeManager::GetTime() + t_time, this, t_alarmID, this->RegData[t_alarmID].m_StorageEntryRef);
}

void Alarmable::AlarmDeRegistration(Alarm::ID t_alarmID)
{
	if (this->RegData[t_alarmID].m_registrationState == RegistrationState::PENDING_DEREGISTRATION)
	{
		this->RegData[t_alarmID].m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;

		SceneAttorney::Registration::GetAlarmMgr()->DeRegister(this->RegData[t_alarmID].m_StorageEntryRef);
	}

}

void Alarmable::SubmitAlarmRegistration(Alarm::ID t_alarmID, float t_time)
{
	if (this->RegData[t_alarmID].m_registrationState == RegistrationState::CURRENTLY_DEREGISTERED)
	{
		this->RegData[t_alarmID].m_registrationState = RegistrationState::PENDING_REGISTRATION;

		this->m_timeData[t_alarmID] = t_time;

		SceneManager::GetCurrentScene()->SubmitCommand(this->RegData[t_alarmID].m_alarmRegistrationCommand);
	}
}

void Alarmable::SubmitAlarmDeRegistration(Alarm::ID t_alarmID)
{
	if(this->RegData[t_alarmID].m_registrationState == RegistrationState::CURRENTLY_REGISTERED)
	{
		this->RegData[t_alarmID].m_registrationState = RegistrationState::PENDING_DEREGISTRATION;

		SceneManager::GetCurrentScene()->SubmitCommand(this->RegData[t_alarmID].m_alarmDeRegistrationCommand);
	}
}

float Alarmable::GetAlarmTime(Alarm::ID t_alarmID)
{
	return this->m_timeData[t_alarmID];
}


