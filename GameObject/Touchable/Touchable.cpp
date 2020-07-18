#include "Touchable.h"
#include "SceneManager.h"
#include "TouchRegistrationCommand.h"
#include "TouchDeRegistrationCommand.h"
#include "Selectable.h"

void Touchable::Selection(Selectable* selectedobj)
{
	selectedobj->Selected();
}

void Touchable::SubmitMouseRegistration(AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event)
{
	Touchable::MouseMapIt it = this->m_activeKeys.find(std::make_pair(t_key, t_event));

	//Confirm that this key/event pair is not registered
	assert(it == this->m_activeKeys.end());

	//create storage data for indiv. key
	KeyRegistrationData* registrationData = new KeyRegistrationData;
	registrationData->m_touchRegistrationCommand = new TouchRegistrationCommand(this, t_key, t_event);
	registrationData->m_touchDeRegistrationCommand = new TouchDeRegistrationCommand(this, t_key, t_event, registrationData->m_storageKeyRef);
	registrationData->m_registrationState = RegistrationState::PENDING_REGISTRATION;

	//add data to key map
	this->m_activeKeys.insert({ std::make_pair(t_key, t_event), registrationData });

	SceneManager::GetCurrentScene()->SubmitCommand(registrationData->m_touchRegistrationCommand);
}

void Touchable::SubmitMouseDeRegistration(AZUL_MOUSE k, MOUSE_EVENT_TYPE e)
{
	Touchable::MouseMapIt it = this->m_activeKeys.find(std::make_pair(k, e));

	assert(it->second->m_registrationState == RegistrationState::CURRENTLY_REGISTERED);
	it->second->m_registrationState = RegistrationState::PENDING_DEREGISTRATION;

	//Confirm that this key/event pair is registered
	assert(it != this->m_activeKeys.end());

	SceneManager::GetCurrentScene()->SubmitCommand((it)->second->m_touchDeRegistrationCommand);
}

void Touchable::MouseRegistration(AZUL_MOUSE k, MOUSE_EVENT_TYPE e)
{
	DebugMsg::out("\n TOUCHABLE: ---- > Mouse Action Registration ");

	Touchable::MouseMapIt it = this->m_activeKeys.find(std::make_pair(k, e));

	assert(it->second->m_registrationState == RegistrationState::PENDING_REGISTRATION);
	it->second->m_registrationState = RegistrationState::CURRENTLY_REGISTERED;

	SceneAttorney::Registration::GetTouchMgr()->RegisterSingleMouseAction(this, k, e, it->second->m_storageKeyRef);
}

void Touchable::MouseDeRegistration(AZUL_MOUSE k, MOUSE_EVENT_TYPE e)
{
	DebugMsg::out("\n TOUCHABLE: ---- > Mouse Action DeRegistration ");

	Touchable::MouseMapIt t_indivKey = this->m_activeKeys.find(std::make_pair(k, e));

	assert(t_indivKey->second->m_registrationState == RegistrationState::PENDING_DEREGISTRATION);
	t_indivKey->second->m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;

	SceneAttorney::Registration::GetTouchMgr()->DeRegisterSingleMouseAction(k, e, t_indivKey->second->m_storageKeyRef);

	//delete individual data
	delete t_indivKey->second->m_touchRegistrationCommand;
	delete t_indivKey->second->m_touchDeRegistrationCommand;
	delete t_indivKey->second;

	this->m_activeKeys.erase(t_indivKey);
}

void Touchable::FastMouseRegistration(AZUL_MOUSE k, MOUSE_EVENT_TYPE e)
{

	Touchable::MouseMapIt it = this->m_activeKeys.find(std::make_pair(k, e));

	//Confirm that this key/event pair is not registered
	assert(it == this->m_activeKeys.end());

	//create storage data for indiv. key
	KeyRegistrationData* registrationData = new KeyRegistrationData;
	registrationData->m_touchRegistrationCommand = new TouchRegistrationCommand(this, k, e);
	registrationData->m_touchDeRegistrationCommand = new TouchDeRegistrationCommand(this, k, e, registrationData->m_storageKeyRef);
	registrationData->m_registrationState = RegistrationState::PENDING_REGISTRATION;

	//add data to key map
	this->m_activeKeys.insert({ std::make_pair(k, e), registrationData });

	MouseRegistration(k, e);
}

Touchable::~Touchable()
{
	for (auto key : this->m_activeKeys) {
		delete key.second->m_touchRegistrationCommand;
		delete key.second->m_touchDeRegistrationCommand;
		delete key.second;
	}
}
