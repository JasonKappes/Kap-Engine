#include "OldRotationCommand.h"
#include "Serializable.h"

OldRotationCommand::OldRotationCommand(Serializable& serializable, Matrix rot)
	: m_serializable(&serializable), m_oldRotation(rot) {}

void OldRotationCommand::Execute()
{
	SerializableAttorney::GameLoop::GetTransform(m_serializable)->rotation = m_oldRotation;
	SerializableAttorney::GameLoop::GetTransform(m_serializable)->UpdateWorld();
}
