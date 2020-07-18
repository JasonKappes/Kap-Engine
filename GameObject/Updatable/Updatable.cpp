#include "Updatable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "UpdateRegistrationCommand.h"
#include "UpdateDeRegistrationCommand.h"

Updatable::Updatable()
{
	this->m_registrationCommand = new UpdateRegistrationCommand(this);
	this->m_deregistrationCommand = new UpdateDeRegistrationCommand(this);
}

Updatable::~Updatable()
{
	delete this->m_registrationCommand;
	delete this->m_deregistrationCommand;
}

void Updatable::SceneRegistration() 
{ 
	assert(this->m_updatableRegistrationState == RegistrationState::PENDING_REGISTRATION);

	this->m_updatableRegistrationState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Registration::GetUpdateMgr()->Register(this, this->m_deleteReference);
}

void Updatable::SceneDeRegistration() 
{ 
	assert(this->m_updatableRegistrationState == RegistrationState::PENDING_DEREGISTRATION);

	this->m_updatableRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Registration::GetUpdateMgr()->Deregister(this->m_deleteReference);
}

void Updatable::SubmitUpdateRegistration()
{
	assert(this->m_updatableRegistrationState == RegistrationState::CURRENTLY_DEREGISTERED);

	this->m_updatableRegistrationState = RegistrationState::PENDING_REGISTRATION;

	SceneManager::GetCurrentScene()->SubmitCommand(this->m_registrationCommand);
}

void Updatable::SubmitUpdateDeRegistration()
{
	assert(this->m_updatableRegistrationState == RegistrationState::CURRENTLY_REGISTERED);

	this->m_updatableRegistrationState = RegistrationState::PENDING_DEREGISTRATION;

	SceneManager::GetCurrentScene()->SubmitCommand(this->m_deregistrationCommand);
}
