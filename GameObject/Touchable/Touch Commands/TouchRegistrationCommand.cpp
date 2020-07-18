#include "TouchRegistrationCommand.h"
#include "TouchableAttorney.h"
#include "Touchable.h"

TouchRegistrationCommand::TouchRegistrationCommand(Touchable* t_ptrTouchable, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event)
{
	this->m_ptrTouchable = t_ptrTouchable;
	this->m_key = t_key;
	this->m_event = t_event;
}

void TouchRegistrationCommand::Execute()
{
	TouchableAttorney::Registration::MouseRegistration(this->m_ptrTouchable, this->m_key, this->m_event);
}

