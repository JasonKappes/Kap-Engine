#ifndef _touchderegistrationcommand
#define _touchderegistrationcommand
#include "SceneRegistrationCommand.h"
#include "SingleMouseEventManager.h"

class Touchable;

class TouchDeRegistrationCommand : public SceneRegistrationCommand
{
public:
	TouchDeRegistrationCommand() = delete;
	TouchDeRegistrationCommand(Touchable*, AZUL_MOUSE, MOUSE_EVENT_TYPE, SingleMouseEventManager::KeyStorageRef&);
	TouchDeRegistrationCommand(const TouchDeRegistrationCommand&) = delete;
	TouchDeRegistrationCommand operator=(const TouchDeRegistrationCommand&) = delete;
	~TouchDeRegistrationCommand() = default;

protected:
	void Execute() override;

private:
	Touchable* m_ptrTouchable;
	SingleMouseEventManager::KeyStorageRef m_delReference;
	AZUL_MOUSE m_key;
	MOUSE_EVENT_TYPE m_event;
};

#endif _touchderegistrationcommand
#pragma once
