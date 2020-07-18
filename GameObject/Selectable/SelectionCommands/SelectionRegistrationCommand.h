#ifndef _selectionregistrationcommand
#define _selectionregistrationcommand
#include "SceneRegistrationCommand.h"

class Selectable;

class SelectionRegistrationCommand : public SceneRegistrationCommand
{
public:
	SelectionRegistrationCommand() = delete;
	SelectionRegistrationCommand(Selectable* t_updatable);
	SelectionRegistrationCommand(const SelectionRegistrationCommand&) = delete;
	SelectionRegistrationCommand operator=(const SelectionRegistrationCommand&) = delete;

protected:
	void Execute() override;

private:
	Selectable* m_ptrSelectable;
};

#endif _selectionregistrationcommand
#pragma once
