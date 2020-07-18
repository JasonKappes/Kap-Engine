#ifndef _selectable
#define _selectable
#include "EventType.h"
#include "Registration.h"
#include "SelectionVolumeBSphere.h"
#include "SelectionVolumeOBB.h"
#include "SelectionTestCommand.h"
#include "SceneAttorney.h"

class SelectionRegistrationCommand;
class SelectionDeRegistrationCommand;
class Touchable;
class SelectionVolume;

class Selectable
{
    friend class SelectableAttorney;
public:

    enum class Volume
    {
        BSPHERE, OBB
    };

     SelectionVolume& GetSelectionVolume();

     virtual void Selected() { DebugMsg::out(" \n base class selected "); }

protected:
    
    void SubmitSelectionRegistration();

    void SubmitSelectionDeRegistration();

    void SetSelectionModel(Selectable::Volume chosenCollisionVolume = Selectable::Volume::BSPHERE)
    {
        switch (chosenCollisionVolume)
        {
        case Selectable::Volume::BSPHERE:
            this->m_SelectionVolume = new SelectionVolumeBsphere(this->selectable_transform);
            break;
        case Selectable::Volume::OBB:
            this->m_SelectionVolume = new SelectionVolumeOBB(this->selectable_transform);
            break;
        default:
            break;
        }
    }

    Transform* selectable_transform;

protected:
    Selectable();
    Selectable(const Selectable&) = delete;
    virtual ~Selectable();

private:
 
    void SceneSelectionRegistration();
    void SceneSelectionDeRegistration();
    void FastSelectionRegistration();
    void FastSelectionDeRegistration();

private:
    RegistrationState m_CollRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
    SelectableManager::SelectableCollRef m_selDelRef;
    SelectionRegistrationCommand* m_selectableRegistrationCommand;
    SelectionDeRegistrationCommand* m_selectableDeRegistrationCommand;
    SelectionVolume* m_SelectionVolume;

};

#endif _selectable
#pragma once