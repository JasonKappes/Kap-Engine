#include "SingleKeyEventManager.h"
#include "InputableAttorney.h"
#include "Inputable.h"
#include <iostream>

SingleKeyEventManager::SingleKeyEventManager(AZUL_KEY t_key){ this->m_key = t_key; }

void SingleKeyEventManager::ProcessKeyEvent()
{
	if (Keyboard::GetKeyState(this->m_key))
	{
		if(this->m_lastFrameState == LASTFRAME_STATUS::RELEASED)			TriggerKeyPress();
		this->m_lastFrameState = LASTFRAME_STATUS::PRESSED;

		TriggerKeyHeld();
	}
	else{
		if (this->m_lastFrameState == LASTFRAME_STATUS::PRESSED)			TriggerKeyRelease();	
		this->m_lastFrameState = LASTFRAME_STATUS::RELEASED;
	}
}

void SingleKeyEventManager::TriggerKeyHeld()
{
	for (auto go : this->m_keyHeldDownCol)
		InputableAttorney::GameLoop::KeyHeld(go, this->m_key);
}

void SingleKeyEventManager::TriggerKeyPress()
{
	for (auto go : this->m_keyPressedCol)
		InputableAttorney::GameLoop::KeyPress(go, this->m_key);
}

void SingleKeyEventManager::TriggerKeyRelease()
{
	for (auto go : this->m_keyReleasedCol)
		InputableAttorney::GameLoop::KeyRelease(go, this->m_key);
}

void SingleKeyEventManager::RegisterInputable(Inputable* t_go, EVENT_TYPE e, KeyStorageRef& t_iterator)
{
	if (e == EVENT_TYPE::PRESS)
	{
		if (this->m_keyPressedCol.find(t_go) == this->m_keyPressedCol.end())			t_iterator = this->m_keyPressedCol.insert(t_go).first;
		else	throw std::runtime_error(" \n SingleKeyEventManager: --- > Inputable already Registered! \n ");
	}
	else if (e == EVENT_TYPE::RELEASE)
	{
		if (this->m_keyReleasedCol.find(t_go) == this->m_keyReleasedCol.end())			t_iterator = this->m_keyReleasedCol.insert(t_go).first;
		else	throw std::runtime_error(" \n SingleKeyEventManager: --- > Inputable already Registered! \n ");
	}
	else if (e == EVENT_TYPE::HELD_DOWN)
	{
		DebugMsg::out("\n single key manager:  KEY HELD DOWN ---> registered ");
		if (this->m_keyHeldDownCol.find(t_go) == this->m_keyHeldDownCol.end())			t_iterator = this->m_keyHeldDownCol.insert(t_go).first;
		else	throw std::runtime_error(" \n SingleKeyEventManager: --- > Inputable already Registered! \n ");
	}

	DebugMsg::out("\n SingleKeyManager inputable -------- >		registered ");
}

void SingleKeyEventManager::DeRegisterInputable(EVENT_TYPE e, KeyStorageRef& t_iterator)
{
	if (e == EVENT_TYPE::PRESS)					this->m_keyPressedCol.erase(t_iterator);		//quick remove
	else if (e == EVENT_TYPE::RELEASE)			this->m_keyReleasedCol.erase(t_iterator);		//quick remove
	else if(e == EVENT_TYPE::HELD_DOWN)			this->m_keyHeldDownCol.erase(t_iterator);		//quick remove

	DebugMsg::out("\n SingleKeyManager key ---------- >		deregistered ");
}
