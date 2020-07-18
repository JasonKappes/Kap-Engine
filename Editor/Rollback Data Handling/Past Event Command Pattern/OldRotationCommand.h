#ifndef _oldrotationcommand
#define _oldrotationcommand
#include "PastEventCommand.h"

class Serializable;

class OldRotationCommand : public PastEventCommand
{
public:
	OldRotationCommand() = delete;
	OldRotationCommand(const OldRotationCommand&) = delete;
	OldRotationCommand operator=(const OldRotationCommand&) = delete;
	~OldRotationCommand() = default;

	OldRotationCommand(Serializable& serializable, Matrix oldrotation);

	void Execute() override;

private:
	Serializable* m_serializable;
	Matrix m_oldRotation;
};

#endif _oldrotationcommand
#pragma once
