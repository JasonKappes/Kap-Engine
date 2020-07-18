#ifndef _serializable
#define _serializable
#include <typeinfo>
#include "SceneAttorney.h"
#include "SerializableManager.h"
#include "Transform.h"

class Transform;

class Serializable
{
    friend class SerializableAttorney;
public:
    Serializable() = default;
    Serializable(Transform*);
    Serializable(const Serializable&);
    Serializable operator=(const Serializable&) = delete;
    virtual ~Serializable() = default;

    jsonData::UserType GetTypeName();

protected:
    template <typename T>
    void SetSerializableGroup()
    {
        SceneAttorney::Registration::GetSerializableMgr()->RegisterSerializable<T>(this);
    }

    void SetSerializableTransform(Transform* s);

private:
    void DeSerialize(jsonData* package);

    void Serialize(int);

    void EditorRender() const;

    void ResetTypeName(SerializableManager::origin);

    void Duplicate() const;

    void Remove();

    void SetSerializableInformation(jsonData::UserType);

    void SetDelIterator(std::multimap<JsonHandler::UserType, Serializable*>::iterator&);

    Transform* GetTransform();

private:
    std::multimap<JsonHandler::UserType, Serializable*>::iterator delRef;
    jsonData::UserType myType;
    Transform* serializable_transform;

};

#endif _serializable
#pragma once
