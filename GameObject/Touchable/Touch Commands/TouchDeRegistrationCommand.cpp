#include "TouchDeRegistrationCommand.h"
#include "TouchableAttorney.h"
#include "Touchable.h"

TouchDeRegistrationCommand::TouchDeRegistrationCommand(Touchable* t_ptrTouchable, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event, SingleMouseEventManager::KeyStorageRef& t_delRef)
{
	this->m_ptrTouchable = t_ptrTouchable;
	this->m_key = t_key;
	this->m_event = t_event;
	this->m_delReference = t_delRef;
}

void TouchDeRegistrationCommand::Execute()
{
	TouchableAttorney::Registration::MouseDeRegistration(this->m_ptrTouchable, this->m_key, this->m_event);
}
