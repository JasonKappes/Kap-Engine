#include "GameObject.h"
#include "GameObjectEntryCommand.h"
#include "GameObjectExitCommand.h"

GameObject::GameObject()
{
	this->m_gameObjectEntryCommand		 = new GameObjectEntryCommand(this);
	this->m_gameObjectExitCommand		 = new GameObjectExitCommand(this);

	this->transform						 = new Transform();

	Serializable::SetSerializableTransform(this->transform);
	Selectable::selectable_transform	 = this->transform;
}

GameObject::~GameObject() 
{ 
	delete this->m_gameObjectEntryCommand; 
	delete this->m_gameObjectExitCommand;
	if (transform->object != nullptr)
	{
		delete GetTransform()->object;
	}
	delete transform;
}

Transform* GameObject::GetTransform() const
{
	return this->transform;
}

void GameObject::SubmitEntry()
{
	this->m_currState = RegistrationState::PENDING_REGISTRATION;
	SceneManager::GetCurrentScene()->SubmitCommand(this->m_gameObjectEntryCommand);
}

void GameObject::SubmitExit()
{
	this->m_currState = RegistrationState::PENDING_DEREGISTRATION;
	SceneManager::GetCurrentScene()->SubmitCommand(this->m_gameObjectExitCommand);
}

void GameObject::ConnectToScene()
{
	assert(this->m_currState == RegistrationState::PENDING_REGISTRATION);
	//GO must not be connected to a scene

	this->m_currState = RegistrationState::CURRENTLY_REGISTERED;
	this->SceneEntry();
}

void GameObject::DisconnectFromScene()
{
	if (this->m_currState == RegistrationState::PENDING_DEREGISTRATION)
	{
		this->m_currState = RegistrationState::CURRENTLY_DEREGISTERED;
		this->SceneExit();
	}
}

