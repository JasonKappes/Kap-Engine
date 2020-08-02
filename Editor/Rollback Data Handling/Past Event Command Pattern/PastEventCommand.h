#ifndef _pasteventcommand
#define _pasteventcommand
#include "Matrix.h"

//This is the base class for the rollback command pattern. The rollback handler executes these commands.
//The behavior changes based on the command executed.
class PastEventCommand
{
public:
	PastEventCommand() = default;
	PastEventCommand(const PastEventCommand&) = delete;
	virtual ~PastEventCommand() = default;

	virtual void Execute() = 0;
};

#endif _pasteventcommand
#pragma once
