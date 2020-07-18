#ifndef _pasteventcommand
#define _pasteventcommand
#include "Matrix.h"

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
