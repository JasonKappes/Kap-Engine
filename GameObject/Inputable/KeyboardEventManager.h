#ifndef _keyboardeventmanager
#define _keyboardeventmanager
#include <map>
#include "SingleKeyEventManager.h"

class Inputable;

class KeyboardEventManager
{

public: // ----> ENGINE METHODS
	KeyboardEventManager();
	KeyboardEventManager(const KeyboardEventManager&) = delete;
	KeyboardEventManager operator=(const KeyboardEventManager&) = delete;
	~KeyboardEventManager();

	void ProcessSingleKeyEvents() const;

	void RegisterSingleKey(Inputable*, AZUL_KEY, EVENT_TYPE, SingleKeyEventManager::KeyStorageRef&);
	void DeRegisterSingleKey(AZUL_KEY, EVENT_TYPE, SingleKeyEventManager::KeyStorageRef&);

private:
	using singleKeyMap = std::map<AZUL_KEY, SingleKeyEventManager*>;
	SingleKeyEventManager* m_singleKey;
	singleKeyMap m_timeLine;
};

#endif _keyboardeventmanager
#pragma once
