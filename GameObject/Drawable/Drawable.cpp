#include "Drawable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "Scene.h"
#include "DrawRegistrationCommand.h"
#include "DrawDeRegistrationCommand.h"

Drawable::Drawable()
{
	this->m_registrationCommand = new DrawRegistrationCommand(this);
	this->m_deregistrationCommand = new DrawDeRegistrationCommand(this);
}

Drawable::~Drawable()
{
	delete this->m_registrationCommand;
	delete this->m_deregistrationCommand;
}

void Drawable::SceneRegistration() 
{ 
	assert(this->m_registrationState == RegistrationState::PENDING_REGISTRATION);
	this->m_registrationState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Registration::GetDrawMgr()->Register(this, this->m_deleteRef);
}

void Drawable::SceneDeRegistration() 
{ 
	assert(this->m_registrationState == RegistrationState::PENDING_DEREGISTRATION);
	this->m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Registration::GetDrawMgr()->Deregister(this->m_deleteRef);
}

void Drawable::SubmitDrawRegistration()
{
	assert(this->m_registrationState == RegistrationState::CURRENTLY_DEREGISTERED);
	this->m_registrationState = RegistrationState::PENDING_REGISTRATION;

	SceneManager::GetCurrentScene()->SubmitCommand(this->m_registrationCommand);
}

void Drawable::SubmitDrawDeRegistration()
{
	assert(this->m_registrationState == RegistrationState::CURRENTLY_REGISTERED);
	this->m_registrationState = RegistrationState::PENDING_DEREGISTRATION;

	SceneManager::GetCurrentScene()->SubmitCommand(this->m_deregistrationCommand);
}