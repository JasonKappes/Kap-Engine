#include "OldPositionCommand.h"
#include "Serializable.h"

OldPositionCommand::OldPositionCommand(Serializable& serializable, Vect pos)
	: m_serializable(&serializable), m_oldPosition(pos) {}

void OldPositionCommand::Execute()
{
	SerializableAttorney::GameLoop::GetTransform(m_serializable)->position = m_oldPosition;
	SerializableAttorney::GameLoop::GetTransform(m_serializable)->UpdateWorld();
}
