#ifndef _touchable
#define _touchable
#include "Registration.h"
#include "MouseEventManager.h"
#include "SceneAttorney.h"
#include <map>
using namespace std;

class TouchRegistrationCommand;
class TouchDeRegistrationCommand;
class Selectable;
class Touchable
{
	friend class TouchableAttorney;
public:
	virtual void Selection(Selectable* selectedobj);

protected: // ---> USER METHODS

	/// <summary>
	/// Register a GameObject to detect a unique key mouse press, release, or hold 
	/// </summary> 
	/// \ingroup Inputable
	void SubmitMouseRegistration(AZUL_MOUSE MouseAction, MOUSE_EVENT_TYPE MouseEvent);

	/// <summary>
	/// De-register detection of an associated event with the mouse
	/// </summary> 
	/// \ingroup Inputable
	void SubmitMouseDeRegistration(AZUL_MOUSE MouseAction, MOUSE_EVENT_TYPE MouseEvent);


	void FindMouseSelections(Touchable* t)
	{
		SceneAttorney::Registration::GetSelectableManager()->ProcessSelections(t);
	}


private: // ---> ENGINE CALLBACKS , USER METHODS (to override)

	/// <summary>
	/// Method to be overriden by a GameObject. 
	/// 
	/// If a certain key is submitted through SubmitMouseRegistration(mouseAction, keyPress), a callback to this function will happen when the submitted key press happens.
	/// </summary> 
	/// \ingroup Inputable
	virtual void MouseActionPressed(AZUL_MOUSE ) {}

	/// <summary>
	/// Method to be overriden by a GameObject. 
	/// 
	/// If a certain key is submitted through SubmitKeyRegistration(key, keyRelease), a callback to this function will happen when the submitted key release happens.
	/// </summary> 
	/// \ingroup Inputable
	virtual void MouseActionReleased(AZUL_MOUSE) {}

	/// <summary>
	/// Method to be overriden by a GameObject. 
	/// 
	/// If a certain key is submitted through SubmitKeyRegistration(key, keyHeld), a callback to this function will happen when the submitted key hold happens.
	/// </summary> 
	/// \ingroup Inputable
	virtual void MouseActionHeld(AZUL_MOUSE) {}

	/// <summary>
	/// Method to be overriden by a GameObject. 
	/// 
	/// Gives the movement direction of the cursor on screen.
	/// </summary> 
	/// \ingroup Inputable
	virtual void MouseDirection(AZUL_MOUSE) {}
protected:
	Touchable() = default;
	Touchable(const Touchable&) = delete;
	virtual ~Touchable();

private:
	struct KeyRegistrationData
	{
		SingleMouseEventManager::KeyStorageRef m_storageKeyRef;
		RegistrationState m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
		TouchRegistrationCommand* m_touchRegistrationCommand;
		TouchDeRegistrationCommand* m_touchDeRegistrationCommand;
	};

	using mouseEvent = pair<AZUL_MOUSE, MOUSE_EVENT_TYPE>;

	map<mouseEvent, KeyRegistrationData*> m_activeKeys;

	using MouseMapIt = map<mouseEvent, KeyRegistrationData*>::iterator;

private: // ---> ENGINE METHODS
	void MouseRegistration(AZUL_MOUSE, MOUSE_EVENT_TYPE);
	void MouseDeRegistration(AZUL_MOUSE, MOUSE_EVENT_TYPE);
	void FastMouseRegistration(AZUL_MOUSE, MOUSE_EVENT_TYPE);
};

#endif _touchable
#pragma once
