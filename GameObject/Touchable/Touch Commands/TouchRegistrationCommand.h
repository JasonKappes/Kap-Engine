#ifndef _touchregistrationcommand
#define _touchregistrationcommand
#include "SceneRegistrationCommand.h"
#include "EventType.h"
#include "AzulCore.h"

class Touchable;

class TouchRegistrationCommand : public SceneRegistrationCommand
{
public:
	TouchRegistrationCommand() = delete;
	TouchRegistrationCommand(Touchable*, AZUL_MOUSE, MOUSE_EVENT_TYPE);
	TouchRegistrationCommand(const TouchRegistrationCommand&) = delete;
	TouchRegistrationCommand operator=(const TouchRegistrationCommand&) = delete;
	~TouchRegistrationCommand() = default;

protected:
	void Execute() override;

private:
	Touchable* m_ptrTouchable;
	AZUL_MOUSE m_key;
	MOUSE_EVENT_TYPE m_event;
};

#endif _touchregistrationcommand
#pragma once
