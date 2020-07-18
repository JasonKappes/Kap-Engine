#ifndef _inputable
#define _inputable
#include "Registration.h"
#include "KeyboardEventManager.h"
#include <map>
using namespace std;

class InputRegistrationCommand;
class InputDeRegistrationCommand;

class Inputable
{
	friend class InputableAttorney;

protected: // ---> USER METHODS

	/// <summary>
	/// Register a GameObject to detect a unique key press, release, or hold 
	/// </summary> 
	/// \ingroup Inputable
	void SubmitKeyRegistration(AZUL_KEY KeyBoardKey, EVENT_TYPE KeyEvent);

	/// <summary>
	/// De-register detection of an associated event with a key
	/// </summary> 
	/// \ingroup Inputable
	void SubmitKeyDeRegistration(AZUL_KEY KeyBoardKey, EVENT_TYPE KeyEvent);

private: // ---> ENGINE CALLBACKS , USER METHODS (to override)

	/// <summary>
	/// Method to be overriden by a GameObject. 
	/// 
	/// If a certain key is submitted through SubmitKeyRegistration(key, keyPress), a callback to this function will happen when the submitted key press happens.
	/// </summary> 
	/// \ingroup Inputable
	virtual void KeyPressed(AZUL_KEY) {}

	/// <summary>
	/// Method to be overriden by a GameObject. 
	/// 
	/// If a certain key is submitted through SubmitKeyRegistration(key, keyRelease), a callback to this function will happen when the submitted key release happens.
	/// </summary> 
	/// \ingroup Inputable
	virtual void KeyReleased(AZUL_KEY ) {}

	/// <summary>
	/// Method to be overriden by a GameObject. 
	/// 
	/// If a certain key is submitted through SubmitKeyRegistration(key, keyHeld), a callback to this function will happen when the submitted key hold happens.
	/// </summary> 
	/// \ingroup Inputable
	virtual void KeyHeld(AZUL_KEY ) {}

protected:
	Inputable() = default;
	Inputable(const Inputable&) = delete;
	virtual ~Inputable();

private:
	struct KeyRegistrationData
	{
		SingleKeyEventManager::KeyStorageRef m_storageKeyRef;
		RegistrationState m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		InputRegistrationCommand* m_inputRegistrationCommand;
		InputDeRegistrationCommand* m_inputDeRegistrationCommand;
	};

	using keyEvent = pair<AZUL_KEY, EVENT_TYPE>;

	map<keyEvent, KeyRegistrationData*> m_activeKeys;

	using KeyMapIt = map<keyEvent, KeyRegistrationData*>::iterator;

private: // ---> ENGINE METHODS
	void KeyRegistration(AZUL_KEY, EVENT_TYPE);
	void KeyDeRegistration(AZUL_KEY, EVENT_TYPE);
	void FastKeyRegistration(AZUL_KEY, EVENT_TYPE);
	void FastKeyDeRegistration(AZUL_KEY, EVENT_TYPE);
};

#endif _inputable
#pragma once
