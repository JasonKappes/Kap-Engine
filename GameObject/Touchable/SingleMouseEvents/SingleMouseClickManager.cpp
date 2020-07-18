#include "SingleMouseClickManager.h"
#include "TouchableAttorney.h"
#include "Touchable.h"
#include <iostream>

SingleMouseClickManager::SingleMouseClickManager(AZUL_MOUSE t_key) 
	: m_lastFrameState(LASTFRAME_STATUS::RELEASED) { this->m_key = t_key; }

void SingleMouseClickManager::ProcessMouseEvent()
{
	if (Mouse::GetKeyState(this->m_key))
	{
		if (this->m_lastFrameState == LASTFRAME_STATUS::RELEASED)			TriggerMousePress();
		this->m_lastFrameState = LASTFRAME_STATUS::PRESSED;

		TriggerMouseHeld();
	}
	else {
		if (this->m_lastFrameState == LASTFRAME_STATUS::PRESSED)			TriggerMouseRelease();
		this->m_lastFrameState = LASTFRAME_STATUS::RELEASED;
	}
}

void SingleMouseClickManager::TriggerMouseHeld()
{
	for (auto go : this->m_mouseHeldDownCol)
		TouchableAttorney::GameLoop::MouseActionHeld(go, this->m_key);
}

void SingleMouseClickManager::TriggerMousePress()
{
	for (auto go : this->m_mousePressedCol)
		TouchableAttorney::GameLoop::MouseActionPress(go, this->m_key);
}

void SingleMouseClickManager::TriggerMouseRelease()
{
	for (auto go : this->m_mouseReleasedCol)
		TouchableAttorney::GameLoop::MouseActionRelease(go, this->m_key);
}

void SingleMouseClickManager::RegisterTouchable(Touchable* t_go, MOUSE_EVENT_TYPE e, KeyStorageRef& t_iterator)
{
	if (e == MOUSE_EVENT_TYPE::PRESS)
	{
		if (this->m_mousePressedCol.find(t_go) == this->m_mousePressedCol.end())			t_iterator = this->m_mousePressedCol.insert(t_go).first;
		else	throw std::runtime_error(" \n SingleMouseClickManager: --- > Touchable already Registered! \n ");
	}
	else if (e == MOUSE_EVENT_TYPE::RELEASE)
	{
		if (this->m_mouseReleasedCol.find(t_go) == this->m_mouseReleasedCol.end())			t_iterator = this->m_mouseReleasedCol.insert(t_go).first;
		else	throw std::runtime_error(" \n SingleMouseClickManager: --- > Touchable already Registered! \n ");
	}
	else if (e == MOUSE_EVENT_TYPE::HELD_DOWN)
	{
		DebugMsg::out("\n single mouse click manager:  KEY HELD DOWN ---> registered ");
		if (this->m_mouseHeldDownCol.find(t_go) == this->m_mouseHeldDownCol.end())			t_iterator = this->m_mouseHeldDownCol.insert(t_go).first;
		else	throw std::runtime_error(" \n SingleMouseClickManager: --- > Touchable already Registered! \n ");
	}

	DebugMsg::out("\n SingleMouseClickManager touchable -------- >		registered ");
}

void SingleMouseClickManager::DeRegisterTouchable(MOUSE_EVENT_TYPE e, KeyStorageRef& t_iterator)
{
	if (e == MOUSE_EVENT_TYPE::PRESS)					this->m_mousePressedCol.erase(t_iterator);		//quick remove
	else if (e == MOUSE_EVENT_TYPE::RELEASE)			this->m_mouseReleasedCol.erase(t_iterator);		//quick remove
	else if (e == MOUSE_EVENT_TYPE::HELD_DOWN)		this->m_mouseHeldDownCol.erase(t_iterator);		//quick remove

	DebugMsg::out("\n SingleMouseClickManager key ---------- >		deregistered ");
}
