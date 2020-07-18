#include "InputRegistrationCommand.h"
#include "InputableAttorney.h"
#include "Inputable.h"

InputRegistrationCommand::InputRegistrationCommand(Inputable* t_ptrInputable, AZUL_KEY t_key, EVENT_TYPE t_event)
{
	this->m_ptrInputable = t_ptrInputable;
	this->m_key = t_key;
	this->m_event = t_event;
}

void InputRegistrationCommand::Execute()
{
	InputableAttorney::Registration::KeyRegistration(this->m_ptrInputable, this->m_key, this->m_event);
}
