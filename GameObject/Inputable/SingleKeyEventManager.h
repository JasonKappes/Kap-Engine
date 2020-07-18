#ifndef _singlekeyeventmanager
#define _singlekeyeventmanager
#include <AzulCore.h>
#include "EventType.h"
#include <unordered_set>

class Inputable;

class SingleKeyEventManager
{
public:
	using InputSet = std::unordered_set<Inputable*>;
	using KeyStorageRef = InputSet::iterator;

private:
	enum class LASTFRAME_STATUS { PRESSED, RELEASED };

public: // ---> ENGINE METHODS
	SingleKeyEventManager() = delete;
	SingleKeyEventManager(AZUL_KEY);
	SingleKeyEventManager(const SingleKeyEventManager&) = delete;
	SingleKeyEventManager operator=(const SingleKeyEventManager&) = delete;
	~SingleKeyEventManager() { DebugMsg::out(" \n SINGLE KEY EVENT MANAGER Destructor "); }

	void ProcessKeyEvent();

	void TriggerKeyPress();
	void TriggerKeyHeld();
	void TriggerKeyRelease();

	void RegisterInputable(Inputable*, EVENT_TYPE e, KeyStorageRef&);
	void DeRegisterInputable(EVENT_TYPE e, KeyStorageRef&);

private:
	AZUL_KEY m_key;
	InputSet m_keyHeldDownCol;
	InputSet m_keyPressedCol;
	InputSet m_keyReleasedCol;
	LASTFRAME_STATUS m_lastFrameState;
};

#endif _singlekeyeventmanager
#pragma once
