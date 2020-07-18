#ifndef _inputregistrationcommand
#define _inputregistrationcommand
#include "SceneRegistrationCommand.h"
#include "EventType.h"
#include "AzulCore.h"

class Inputable;

class InputRegistrationCommand : public SceneRegistrationCommand
{
public:
	InputRegistrationCommand() = delete;
	InputRegistrationCommand(Inputable*, AZUL_KEY, EVENT_TYPE);
	InputRegistrationCommand(const InputRegistrationCommand&) = delete;
	InputRegistrationCommand operator=(const InputRegistrationCommand&) = delete;
	~InputRegistrationCommand() = default;

protected:
	void Execute() override;

private:
	Inputable* m_ptrInputable;
	AZUL_KEY m_key;
	EVENT_TYPE m_event;
};

#endif _inputregistrationcommand
#pragma once
