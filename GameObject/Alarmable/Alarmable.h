#ifndef _alarmable
#define _alarmable
#include "Registration.h"
#include "AlarmID.h"

class AlarmRegistrationCommand;
class AlarmDeRegistrationCommand;

class Alarmable
{
	friend class AlarmableAttorney;

protected: // ----> USER METHODS

	/// <summary>
	/// De-register a currently active alarm the next frame
	/// </summary> 
	/// \ingroup Alarmable
	void SubmitAlarmDeRegistration(Alarm::ID);

	/// <summary>
	/// Register an alarm (1, 2, 3) to trigger a callback to its associated function after the designated time
	/// </summary> 
	/// \ingroup Alarmable
	void SubmitAlarmRegistration(Alarm::ID, float);

protected:
	Alarmable();
	Alarmable(const Alarmable&) = delete;
	virtual ~Alarmable();

private: // --- > ENGINE CALLBACKS, USER METHODS (to override)

	/// <summary>
	/// Alarm 0 to be overriden by all GameObjects. This function is called when the Alarm0 time has been reached.
	/// </summary> 
	/// \ingroup Alarmable
	virtual void Alarm0() {};

	/// <summary>
	/// Alarm 1 to be overriden by all GameObjects. This function is called when the Alarm1 time has been reached.
	/// </summary> 
	/// \ingroup Alarmable
	virtual void Alarm1() {};

	/// <summary>
	/// Alarm 2 to be overriden by all GameObjects. This function is called when the Alarm2 time has been reached.
	/// </summary> 
	/// \ingroup Alarmable
	virtual void Alarm2() {};

private: // ---- >  ENGINE METHODS
	float GetAlarmTime(Alarm::ID);
	void TriggerAlarm(Alarm::ID id);
	void AlarmRegistration(Alarm::ID, float);
	void AlarmDeRegistration(Alarm::ID);

private:
	struct RegistrationData
	{
		RegistrationState m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		Alarm::StorageEntryRef m_StorageEntryRef;
		AlarmRegistrationCommand* m_alarmRegistrationCommand;
		AlarmDeRegistrationCommand* m_alarmDeRegistrationCommand;
	};
	
	RegistrationData RegData[Alarm::NUMBER_OF_ALARMS];

	float m_timeData[Alarm::NUMBER_OF_ALARMS];
};

#endif _alarmable
#pragma once
