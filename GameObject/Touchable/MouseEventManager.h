#ifndef _mouseeventmanager
#define _mouseeventmanager
#include <map>
#include "SingleMouseEventManager.h"

class Touchable;

class MouseEventManager
{

public: // ----> ENGINE METHODS
	MouseEventManager();
	MouseEventManager(const MouseEventManager&) = delete;
	MouseEventManager operator=(const MouseEventManager&) = delete;
	~MouseEventManager();

	void ProcessSingleMouseEvents() const;

	void RegisterSingleMouseAction(Touchable*, AZUL_MOUSE, MOUSE_EVENT_TYPE, SingleMouseEventManager::KeyStorageRef&);
	void DeRegisterSingleMouseAction(AZUL_MOUSE, MOUSE_EVENT_TYPE, SingleMouseEventManager::KeyStorageRef&);

private:
	using singleMouseEventMap = std::map<AZUL_MOUSE, SingleMouseEventManager*>;
	SingleMouseEventManager* m_singleMouseAction;
	singleMouseEventMap m_timeLine;
};

#endif _keyboardeventmanager
#pragma once
