#ifndef _reviveserializablecommand
#define _reviveserializablecommand
#include "PastEventCommand.h"

class Serializable;
class Transform;

class ReviveSerializableCommand : public PastEventCommand
{
public:
	ReviveSerializableCommand() = delete;
	ReviveSerializableCommand(const ReviveSerializableCommand&) = delete;
	ReviveSerializableCommand operator=(const ReviveSerializableCommand&) = delete;
	~ReviveSerializableCommand() = default;

	ReviveSerializableCommand(Serializable& serializable, Transform& old_transform);

	void Execute() override;

private:
	Serializable* m_serializable;
	Transform* m_oldTransform;
};

#endif _reviveserialzablecommand
#pragma once
