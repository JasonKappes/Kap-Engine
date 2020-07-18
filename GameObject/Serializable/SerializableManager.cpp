#include "SerializableManager.h"
#include "Serializable.h"
#include "Raycast.h"
#include "ScreenLog.h"
#include "EmptyObject.h"
#include "ActiveObject.h"
#include "EditorInput.h"
#include "SceneManager.h"


const std::string SerializableManager::fileCreatedID = "0";
const std::string SerializableManager::sourceCreatedID = "1";

SerializableManager::SerializableManager() { cycleInd = this->m_serDataColl.begin(); }

void SerializableManager::WriteSerializables()
{
    SafeDataColl::iterator it;

    if (m_serDataColl.empty()) JsonHandler::EmptyWrite();

    for (it = m_serDataColl.begin(); it != m_serDataColl.end();)
    {
        int typeCount = m_serDataColl.count(it->first);
        SerializableAttorney::Data::Serialize(*it->second, typeCount);
        m_serDataColl.erase(it++);
    }
}

void SerializableManager::AddSerializable(Serializable* t_serializable)
{
    std::multimap<JsonHandler::UserType, Serializable*>::iterator it = m_serDataColl.insert({ t_serializable->GetTypeName(), t_serializable });

    SerializableAttorney::Data::SetDelIterator(t_serializable, it);
}

void SerializableManager::RemoveSerializable(SafeDataColl::iterator it)
{
    this->m_serDataColl.erase(it);
    cycleInd = this->m_serDataColl.end();
}

int SerializableManager::GetTypeCount(std::string type)
{
    return this->m_serDataColl.count(type);
}

void SerializableManager::EditorDraw() const
{
    for (SafeDataColl::const_iterator it = m_serDataColl.begin(); it != m_serDataColl.end(); ++it)
    {
        SerializableAttorney::GameLoop::EditorRender((*it->second));
    }   
}

void SerializableManager::SelectNewlyLoadedObjects(EditorInput* editorObj)
{
    Matrix defaultScale = Matrix(IDENTITY);

    cycleInd = this->m_serDataColl.begin();

    while (cycleInd != this->m_serDataColl.end())
    {
        if (SerializableAttorney::GameLoop::GetTransform(cycleInd->second)->scale.isEqual(defaultScale))
        {
            editorObj->SetActiveSelection(cycleInd->second);
            return;
        }
        else {
            cycleInd++;
        }
    }
}

void SerializableManager::MousePick(EditorInput* editorObj)
{
    SceneManager::Get3DCamera()->getPos(this->campos);

    SafeDataColl::iterator it;
    Vect pos1;
    float radius;

    for (it = m_serDataColl.begin(); it != m_serDataColl.end(); ++it)
    {
        pos1 = SerializableAttorney::GameLoop::GetTransform(it->second)->position;
        radius = SerializableAttorney::GameLoop::GetTransform(it->second)->GetRadius();

        if (Raycast::MouseSphereCollision(pos1, radius))
        {
            selectedObjects.push(it->second);
        }
    }

    //empty 
    if (this->selectedObjects.empty())
    {
        editorObj->SetEmptySelection();
        return;
    }

    Serializable* selectedObj = selectedObjects.top();
    float smallestRad = SerializableAttorney::GameLoop::GetTransform(selectedObj)->GetRadius();
    selectedObjects.pop();

    while (!selectedObjects.empty())
    {
        float newRad = SerializableAttorney::GameLoop::GetTransform(selectedObjects.top())->GetRadius();

        if (newRad < smallestRad)
        {
            smallestRad = newRad;
            selectedObj = selectedObjects.top();
        }
        selectedObjects.pop();
    } 

    editorObj->SetActiveSelection(selectedObj);
    return;
}

void SerializableManager::GetSelectionDistance(float& dist, const Vect& position)
{
    dist = (campos - position).mag();
}
