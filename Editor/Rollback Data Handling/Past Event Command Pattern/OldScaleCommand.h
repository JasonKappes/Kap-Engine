#ifndef _oldscalecommand
#define _oldscalecommand
#include "PastEventCommand.h"

class Serializable;

//This command is generated when the scale of an object is changed. It holds old scale object data.
class OldScaleCommand : public PastEventCommand
{
public:
	OldScaleCommand() = delete;
	OldScaleCommand(const OldScaleCommand&) = delete;
	OldScaleCommand operator=(const OldScaleCommand&) = delete;
	~OldScaleCommand() = default;

	OldScaleCommand(Serializable& serializable, Matrix oldscale);

	void Execute() override;

private:
	Serializable* m_serializable;
	Matrix m_oldScale;
};

#endif _oldscalecommand
#pragma once
