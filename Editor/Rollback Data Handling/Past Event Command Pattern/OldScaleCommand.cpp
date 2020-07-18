#include "OldScaleCommand.h"
#include "Serializable.h"
#include "SerializableAttorney.h"

OldScaleCommand::OldScaleCommand(Serializable& serializable, Matrix scale)
	: m_serializable(&serializable), m_oldScale(scale) {}

void OldScaleCommand::Execute()
{
	SerializableAttorney::GameLoop::GetTransform(m_serializable)->scale = m_oldScale;
	SerializableAttorney::GameLoop::GetTransform(m_serializable)->UpdateWorld();
}
