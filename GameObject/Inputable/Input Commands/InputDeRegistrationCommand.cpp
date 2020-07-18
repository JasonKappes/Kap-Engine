#include "InputDeRegistrationCommand.h"
#include "InputableAttorney.h"
#include "Inputable.h"

InputDeRegistrationCommand::InputDeRegistrationCommand(Inputable* t_inputable, AZUL_KEY t_key, EVENT_TYPE t_event, SingleKeyEventManager::KeyStorageRef& t_delRef)
{
	this->m_ptrInputable = t_inputable;
	this->m_key = t_key;
	this->m_event = t_event;
	this->m_delReference = t_delRef;
}

void InputDeRegistrationCommand::Execute()
{
	InputableAttorney::Registration::KeyDeRegistration(this->m_ptrInputable, this->m_key, this->m_event);
}
