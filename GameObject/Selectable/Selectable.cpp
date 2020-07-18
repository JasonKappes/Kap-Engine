#include "Selectable.h"
#include "SelectionRegistrationCommand.h"
#include "SelectionDeRegistrationCommand.h"
#include "SceneManager.h"
#include "Transform.h"

Selectable::Selectable()
{
	this->m_selectableRegistrationCommand	= new SelectionRegistrationCommand(this);
	this->m_selectableDeRegistrationCommand	= new SelectionDeRegistrationCommand(this);
	this->m_SelectionVolume					= nullptr;
}

void Selectable::SceneSelectionRegistration()
{
	DebugMsg::out("\n COLLIDABLE: -----> Registration ");
	assert(this->m_CollRegistrationState == RegistrationState::PENDING_REGISTRATION);
	this->m_CollRegistrationState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Registration::GetSelectableManager()->Register(this, m_selDelRef);
}

void Selectable::SceneSelectionDeRegistration()
{
	DebugMsg::out("\n SELECTABLE : -----> De - Registration ");
	assert(this->m_CollRegistrationState == RegistrationState::PENDING_DEREGISTRATION);
	this->m_CollRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Registration::GetSelectableManager()->Deregister(this->m_selDelRef);
}
 
SelectionVolume& Selectable::GetSelectionVolume()
{
	Vect minn = this->m_SelectionVolume->objtransform->object->getModel()->getMinAABB();
	Vect maxx = this->m_SelectionVolume->objtransform->object->getModel()->getMaxAABB();
	return *this->m_SelectionVolume;
}

void Selectable::SubmitSelectionRegistration()
{
	assert(this->m_CollRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	this->m_CollRegistrationState = RegistrationState::PENDING_REGISTRATION;

	SceneManager::GetCurrentScene()->SubmitCommand(this->m_selectableRegistrationCommand);
}

void Selectable::SubmitSelectionDeRegistration()
{
	assert(this->m_CollRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	this->m_CollRegistrationState = RegistrationState::PENDING_DEREGISTRATION;

	SceneManager::GetCurrentScene()->SubmitCommand(this->m_selectableDeRegistrationCommand);
}

void Selectable::FastSelectionRegistration()
{
	assert(this->m_CollRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	this->m_CollRegistrationState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Registration::GetSelectableManager()->Register(this, m_selDelRef);
}

void Selectable::FastSelectionDeRegistration()
{
	assert(this->m_CollRegistrationState == RegistrationState::CURRENTLY_REGISTERED);
	this->m_CollRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Registration::GetSelectableManager()->Deregister(m_selDelRef);
}


Selectable::~Selectable()
{
	delete this->m_SelectionVolume;
	delete this->m_selectableRegistrationCommand;
	delete this->m_selectableDeRegistrationCommand;
}