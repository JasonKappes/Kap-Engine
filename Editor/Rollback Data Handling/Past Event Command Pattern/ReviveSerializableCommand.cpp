#include "ReviveSerializableCommand.h"
#include "SerializableManager.h"
#include "SceneAttorney.h"
#include "Serializable.h"

ReviveSerializableCommand::ReviveSerializableCommand(Serializable& serializable, Transform& old_transform)
	: m_serializable(&serializable), m_oldTransform(&old_transform) {}

void ReviveSerializableCommand::Execute()
{
	SceneAttorney::Registration::GetSerializableMgr()->AddSerializable(m_serializable);
	SerializableAttorney::GameLoop::GetTransform(m_serializable)->UpdateWorld();
}
