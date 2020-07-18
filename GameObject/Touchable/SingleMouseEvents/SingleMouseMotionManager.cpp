#include "SingleMouseMotionManager.h"
#include "TouchableAttorney.h"
#include "Touchable.h"
#include "CursorAttorney.h"

SingleMouseMotionManager::SingleMouseMotionManager(AZUL_MOUSE t_direction) 
{ 
	this->m_direction = t_direction;

	pastMousePosition.first = 0.0f;
	pastMousePosition.second = 0.0f;
}

void SingleMouseMotionManager::ProcessMouseEvent()
{
	if (CursorAttorney::GetMouseMovement(m_direction))	TriggerMouseDirection();
}

void SingleMouseMotionManager::TriggerMouseDirection()
{
	for (auto go : this->m_mouseDirectionCol)
		TouchableAttorney::GameLoop::MouseDirection(go, this->m_direction);
}

void SingleMouseMotionManager::RegisterTouchable(Touchable* t_go, MOUSE_EVENT_TYPE, KeyStorageRef& t_iterator)
{
		if (this->m_mouseDirectionCol.find(t_go) == this->m_mouseDirectionCol.end())			t_iterator = this->m_mouseDirectionCol.insert(t_go).first;
		else	throw std::runtime_error(" \n SingleMouseMotionManager: --- > Touchable already Registered! \n ");

	DebugMsg::out("\n SingleMouseEventManager touchable -------- >		registered ");
}

void SingleMouseMotionManager::DeRegisterTouchable(MOUSE_EVENT_TYPE , KeyStorageRef& t_iterator)
{
	this->m_mouseDirectionCol.erase(t_iterator);		//quick remove

	DebugMsg::out("\n SingleMouseMotionManager key ---------- >		deregistered ");
}
