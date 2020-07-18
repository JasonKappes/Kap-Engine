#include "SerializableAttorney.h"
#include "Serializable.h"

void SerializableAttorney::Data::Serialize(Serializable& t_serializable, int typeCount)
{
	t_serializable.Serialize(typeCount);
}

void SerializableAttorney::Data::DeSerialize(Serializable* t_serializable, jsonData* package)
{
	t_serializable->DeSerialize(package);
}

void SerializableAttorney::Data::SetSerializableInformation(Serializable* t_serializable, jsonData::UserType type)
{
	t_serializable->SetSerializableInformation(type);
}

void SerializableAttorney::Data::SetDelIterator(Serializable* t_serializable, std::multimap<JsonHandler::UserType, Serializable*>::iterator& it)
{
	t_serializable->SetDelIterator(it);
}

void SerializableAttorney::GameLoop::EditorRender(const Serializable& t_serializable)
{
	t_serializable.serializable_transform->UpdateWorld();
	t_serializable.EditorRender();
}

void SerializableAttorney::GameLoop::Duplicate(const Serializable& t_serializable)
{
	t_serializable.Duplicate();
}

void SerializableAttorney::GameLoop::Remove(Serializable* t_serializable)
{
	t_serializable->Remove();
}

Transform* SerializableAttorney::GameLoop::GetTransform(Serializable* t_serializable)
{
	return t_serializable->GetTransform();
}

