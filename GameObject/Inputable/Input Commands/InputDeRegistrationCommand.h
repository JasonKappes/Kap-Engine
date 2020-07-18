#ifndef _inputderegistrationcommand
#define _inputderegistrationcommand
#include "SceneRegistrationCommand.h"
#include "SingleKeyEventManager.h"

class Inputable;

class InputDeRegistrationCommand : public SceneRegistrationCommand
{
public:
	InputDeRegistrationCommand() = delete;
	InputDeRegistrationCommand(Inputable*, AZUL_KEY, EVENT_TYPE, SingleKeyEventManager::KeyStorageRef&);
	InputDeRegistrationCommand(const InputDeRegistrationCommand&) = delete;
	InputDeRegistrationCommand operator=(const InputDeRegistrationCommand&) = delete;
	~InputDeRegistrationCommand() = default;

protected:
	void Execute() override;

private:
	Inputable* m_ptrInputable;
	SingleKeyEventManager::KeyStorageRef m_delReference;
	AZUL_KEY m_key;
	EVENT_TYPE m_event;
};

#endif _inputderegistrationcommand
#pragma once
