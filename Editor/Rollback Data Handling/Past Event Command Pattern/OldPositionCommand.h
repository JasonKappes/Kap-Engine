#ifndef _oldpositioncommand
#define _oldpositioncommand
#include "PastEventCommand.h"

class Serializable;

class OldPositionCommand : public PastEventCommand
{
public:
	OldPositionCommand() = delete;
	OldPositionCommand(const OldPositionCommand&) = delete;
	OldPositionCommand operator=(const OldPositionCommand&) = delete;
	~OldPositionCommand() = default;

	OldPositionCommand(Serializable& serializable, Vect old_transform);

	void Execute() override;

private:
	Serializable* m_serializable;
	Vect m_oldPosition;
};

#endif _oldpositioncommand
#pragma once
