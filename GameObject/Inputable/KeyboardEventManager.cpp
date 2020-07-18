#include "KeyboardEventManager.h"

KeyboardEventManager::KeyboardEventManager() : m_singleKey(nullptr) { DebugMsg::out("  keyboard "); }

KeyboardEventManager::~KeyboardEventManager()
{
	auto singleKeyManager = this->m_timeLine.begin();
	while (singleKeyManager != this->m_timeLine.end())
	{
		delete singleKeyManager->second;
		this->m_timeLine.erase(singleKeyManager++);
	}

	DebugMsg::out("\n KeyboardEventManager destructor: SingleKeyCollection ------ > size: %d ", this->m_timeLine.size());
}

void KeyboardEventManager::ProcessSingleKeyEvents() const
{
	for (auto keyEvent : this->m_timeLine)
		keyEvent.second->ProcessKeyEvent();

}

void KeyboardEventManager::RegisterSingleKey(Inputable* t_inputable, AZUL_KEY t_key, EVENT_TYPE t_event, SingleKeyEventManager::KeyStorageRef& t_iterator)
{
	if (this->m_timeLine.find(t_key) == this->m_timeLine.end()) //check for key... if does not exist, create a new key
	{
		DebugMsg::out("\n KeyBoardEventManager: REGISTERED new single key manager \n");
		this->m_timeLine.insert(singleKeyMap::value_type(t_key, new SingleKeyEventManager(t_key)));
	}

	//register new GO to singleKeyManager
	this->m_timeLine[t_key]->RegisterInputable(t_inputable, t_event, t_iterator);
}

void KeyboardEventManager::DeRegisterSingleKey(AZUL_KEY t_key, EVENT_TYPE t_event, SingleKeyEventManager::KeyStorageRef& t_iterator)
{
	DebugMsg::out("\n KeyBoardEventManager: DE-REGISTERED a single key manager \n");

	assert(this->m_timeLine.size() > 0);

	this->m_timeLine[t_key]->DeRegisterInputable(t_event, t_iterator);
}
