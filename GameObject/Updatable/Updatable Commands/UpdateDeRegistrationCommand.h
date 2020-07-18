#ifndef _updatederegistrationcommand
#define _updatederegistrationcommand
#include "SceneRegistrationCommand.h"

class Updatable;

class UpdateDeRegistrationCommand : public SceneRegistrationCommand
{
public:
	UpdateDeRegistrationCommand() = delete;
	UpdateDeRegistrationCommand(Updatable* t_updatable);
	UpdateDeRegistrationCommand(const UpdateDeRegistrationCommand&) = delete;
	UpdateDeRegistrationCommand operator=(const UpdateDeRegistrationCommand&) = delete;

protected:
	void Execute() override;

private:
	Updatable* m_ptrUpdatable;
};

#endif _updateregistrationcommand
#pragma once
