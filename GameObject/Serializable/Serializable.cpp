#include "DebugOut.h"
#include "GameObject.h"

Serializable::Serializable(Transform* t)
{
	this->serializable_transform = t;
}

Serializable::Serializable(const Serializable& serializable)
{
	this->serializable_transform = new Transform(*serializable.serializable_transform);
	this->myType		= std::string(serializable.myType);
}

void Serializable::EditorRender() const
{
	this->serializable_transform->Render();
}

jsonData::UserType Serializable::GetTypeName()
{
	return this->myType;
}

void Serializable::SetSerializableTransform(Transform* s)
{
	this->serializable_transform = s;
}

void Serializable::DeSerialize(jsonData* package)
{
	this->serializable_transform->position           = package->GetPosition();
	this->serializable_transform->rotation			= package->GetRotation();
	this->serializable_transform->scale				= package->GetScale();
}

void Serializable::SetSerializableInformation(jsonData::UserType type)
{
	this->myType	  = type;
}

void Serializable::ResetTypeName(SerializableManager::origin source)
{
	//trim existing identifier
	this->myType = this->myType.substr(0, this->myType.size() - 1);

	//set new identifier (FILE created, or SOURCE created)
	if (source == SerializableManager::origin::FILE)
	{
		this->myType = this->myType + SerializableManager::fileCreatedID;
	}
	else {
		this->myType = this->myType + SerializableManager::sourceCreatedID;
	}
}

void Serializable::Duplicate() const
{
	Serializable* newObject = new Serializable(*this);
	newObject->ResetTypeName(SerializableManager::origin::FILE);
	SceneAttorney::Registration::GetSerializableMgr()->AddSerializable(newObject);
}

void Serializable::Remove()
{
	SceneAttorney::Registration::GetSerializableMgr()->RemoveSerializable(this->delRef);
}

Transform* Serializable::GetTransform()
{
	return serializable_transform;
}

void Serializable::SetDelIterator(std::multimap<JsonHandler::UserType, Serializable*>::iterator& it)
{
	this->delRef = it;
}

void Serializable::Serialize(int t_typecount)
{
	//store world data and user type information
	jsonData* m_jsonData = new jsonData(serializable_transform->position, serializable_transform->rotation, serializable_transform->scale,
		Serializable::GetTypeName(), t_typecount);

	JsonHandler::Serialize(m_jsonData);

	delete m_jsonData;
}
