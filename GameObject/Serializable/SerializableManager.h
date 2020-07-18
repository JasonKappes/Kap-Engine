#ifndef _serializablemanager
#define _serializablemanager
#include "SerializableAttorney.h"
#include "JsonHandler.h"
#include <map>
#include <stack>

class Serializable;
class JsonData;
class EditorInput;

class SerializableManager
{
public:
    using SafeDataColl = std::multimap<JsonHandler::UserType, Serializable*>;
    SerializableManager();
    SerializableManager(const SerializableManager&) = delete;
    SerializableManager operator=(const SerializableManager&) = delete;
    ~SerializableManager() = default;
public:
    enum class origin { FILE = 0, SOURCE_CODE = 1 };

public:

    void WriteSerializables();

    void EditorDraw() const;

    void MousePick(EditorInput*);

    void SelectNewlyLoadedObjects(EditorInput*);

    void AddSerializable(Serializable*);

    void RemoveSerializable(std::multimap<JsonHandler::UserType, Serializable*>::iterator);

    int GetTypeCount(std::string);

public:

    template <typename type>
    void RegisterSerializable(Serializable* t_serializable)
    {

        if (!JsonHandler::WaitingData()) SerializableManager::RegisterSourceCodeObject<type>(t_serializable);
        else                             SerializableManager::RegisterFileObject<type>(t_serializable);

        JsonHandler::LoadFileObjects<type>();
    }

    template <typename type>
    void RegisterSourceCodeObject(Serializable* t_serializable)
    {
        jsonData::UserType myType = std::string(typeid(type).name()) + sourceCreatedID;

        std::multimap<JsonHandler::UserType, Serializable*>::iterator it = m_serDataColl.insert({ myType, t_serializable });

        SerializableAttorney::Data::SetDelIterator(t_serializable, it);

        SerializableAttorney::Data::SetSerializableInformation(t_serializable, myType);

        JsonHandler::DeSerialize(t_serializable);
    }

    template <typename type>
    void RegisterFileObject(Serializable* t_serializable)
    {
        jsonData::UserType myType = std::string(typeid(type).name()) + fileCreatedID;

        std::multimap<JsonHandler::UserType, Serializable*>::iterator it = m_serDataColl.insert({ myType, t_serializable });

        SerializableAttorney::Data::SetDelIterator(t_serializable, it);

        SerializableAttorney::Data::SetSerializableInformation(t_serializable, myType);

        JsonHandler::GetWaitingPackage(t_serializable);
    }

public:
    static const std::string fileCreatedID;
    static const std::string sourceCreatedID;

private:
    void GetSelectionDistance(float&, const Vect& pos);

private:
    SafeDataColl m_serDataColl;
    SafeDataColl::iterator cycleInd;
    std::stack<Serializable*> selectedObjects;
    Vect campos;
};
#endif _serializablemanager
#pragma once

