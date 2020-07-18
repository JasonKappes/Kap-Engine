#include "Inputable.h"
#include "SceneManager.h"
#include "SceneAttorney.h"
#include "InputRegistrationCommand.h"
#include "InputDeRegistrationCommand.h"


void Inputable::SubmitKeyRegistration(AZUL_KEY t_key, EVENT_TYPE t_event)
{
	Inputable::KeyMapIt it = this->m_activeKeys.find(std::make_pair(t_key, t_event));

	//Confirm that this key/event pair is not registered
	assert(it == this->m_activeKeys.end());

	//create storage data for indiv. key
	KeyRegistrationData* registrationData = new KeyRegistrationData;
	registrationData->m_inputRegistrationCommand = new InputRegistrationCommand(this, t_key, t_event);
	registrationData->m_inputDeRegistrationCommand = new InputDeRegistrationCommand(this, t_key, t_event, registrationData->m_storageKeyRef);
	registrationData->m_registrationState = RegistrationState::PENDING_REGISTRATION;

	//add data to key map
	this->m_activeKeys.insert({ std::make_pair(t_key, t_event), registrationData });

	SceneManager::GetCurrentScene()->SubmitCommand(registrationData->m_inputRegistrationCommand);
}

void Inputable::SubmitKeyDeRegistration(AZUL_KEY k, EVENT_TYPE e)
{
	Inputable::KeyMapIt it = this->m_activeKeys.find(std::make_pair(k, e));

	assert(it->second->m_registrationState == RegistrationState::CURRENTLY_REGISTERED);
	it->second->m_registrationState = RegistrationState::PENDING_DEREGISTRATION;

	//Confirm that this key/event pair is registered
	assert(it != this->m_activeKeys.end());

	SceneManager::GetCurrentScene()->SubmitCommand((it)->second->m_inputDeRegistrationCommand);
}

void Inputable::KeyRegistration(AZUL_KEY k, EVENT_TYPE e)
{
	DebugMsg::out("\n INPUTABLE: ---- > KeyRegistration ");
	
	Inputable::KeyMapIt it = this->m_activeKeys.find( std::make_pair(k, e) );

	assert(it->second->m_registrationState == RegistrationState::PENDING_REGISTRATION);
	it->second->m_registrationState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Registration::GetInputMgr()->RegisterSingleKey(this, k, e, it->second->m_storageKeyRef);
}

void Inputable::KeyDeRegistration(AZUL_KEY k, EVENT_TYPE e)
{
	DebugMsg::out("\n INPUTABLE: ---- > KeyDeRegistration ");

	Inputable::KeyMapIt t_indivKey = this->m_activeKeys.find (std::make_pair(k, e) );

	assert(t_indivKey->second->m_registrationState == RegistrationState::PENDING_DEREGISTRATION);
	t_indivKey->second->m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Registration::GetInputMgr()->DeRegisterSingleKey(k, e, t_indivKey->second->m_storageKeyRef);

	//delete individual data
	delete t_indivKey->second->m_inputRegistrationCommand;
	delete t_indivKey->second->m_inputDeRegistrationCommand;
	delete t_indivKey->second;

	this->m_activeKeys.erase(t_indivKey);
}

void Inputable::FastKeyRegistration(AZUL_KEY k, EVENT_TYPE e)
{

	Inputable::KeyMapIt it = this->m_activeKeys.find(std::make_pair(k, e));

	//Confirm that this key/event pair is not registered
	assert(it == this->m_activeKeys.end());

	//create storage data for indiv. key
	KeyRegistrationData* registrationData = new KeyRegistrationData;
	registrationData->m_inputRegistrationCommand = new InputRegistrationCommand(this, k, e);
	registrationData->m_inputDeRegistrationCommand = new InputDeRegistrationCommand(this, k, e, registrationData->m_storageKeyRef);
	registrationData->m_registrationState = RegistrationState::PENDING_REGISTRATION;

	//add data to key map
	this->m_activeKeys.insert({ std::make_pair(k, e), registrationData });

	KeyRegistration(k, e);
}

void Inputable::FastKeyDeRegistration(AZUL_KEY k, EVENT_TYPE e)
{
	Inputable::KeyMapIt t_indivKey = this->m_activeKeys.find(std::make_pair(k, e));

	t_indivKey->second->m_registrationState = RegistrationState::PENDING_DEREGISTRATION;

	KeyDeRegistration(k, e);

}

Inputable::~Inputable()
{
	for (auto key : this->m_activeKeys) {
		delete key.second->m_inputRegistrationCommand;
		delete key.second->m_inputDeRegistrationCommand;
		delete key.second;
	}
}
