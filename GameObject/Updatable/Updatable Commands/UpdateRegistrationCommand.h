#ifndef _updateregistrationcommand
#define _updateregistrationcommand
#include "SceneRegistrationCommand.h"

class Updatable;

class UpdateRegistrationCommand : public SceneRegistrationCommand
{
public:
	UpdateRegistrationCommand() = delete;
	UpdateRegistrationCommand(Updatable* t_updatable);
	UpdateRegistrationCommand(const UpdateRegistrationCommand&) = delete;
	UpdateRegistrationCommand operator=(const UpdateRegistrationCommand&) = delete;

protected:
	void Execute() override;

private: 
	Updatable* m_ptrUpdatable;
};

#endif _updateregistrationcommand
#pragma once
