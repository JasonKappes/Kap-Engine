#ifndef _selectionderegistrationcommand
#define _selectionderegistrationcommand
#include "SceneRegistrationCommand.h"

class Selectable;

class SelectionDeRegistrationCommand : public SceneRegistrationCommand
{
public:
	SelectionDeRegistrationCommand() = delete;
	SelectionDeRegistrationCommand(Selectable* t_updatable);
	SelectionDeRegistrationCommand(const SelectionDeRegistrationCommand&) = delete;
	SelectionDeRegistrationCommand operator=(const SelectionDeRegistrationCommand&) = delete;

protected:
	void Execute() override;

private:
	Selectable* m_ptrSelectable;
};

#endif _selectionderegistrationcommand
#pragma once
