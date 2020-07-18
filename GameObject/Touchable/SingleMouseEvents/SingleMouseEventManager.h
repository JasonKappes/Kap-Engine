#ifndef _singlemouseeventmanager
#define _singlemouseeventmanager
#include <AzulCore.h>
#include "EventType.h"
#include <unordered_set>

class Touchable;

class SingleMouseEventManager
{
public:
	using TouchSet = std::unordered_set<Touchable*>;
	using KeyStorageRef = TouchSet::iterator;

public: // ---> ENGINE METHODS
	SingleMouseEventManager() = default;
	SingleMouseEventManager(const SingleMouseEventManager&) = delete;
	virtual ~SingleMouseEventManager() {}

	virtual void ProcessMouseEvent() = 0;

	virtual void RegisterTouchable(Touchable*, MOUSE_EVENT_TYPE e, KeyStorageRef&) = 0;
	virtual void DeRegisterTouchable(MOUSE_EVENT_TYPE e, KeyStorageRef&) = 0;
};

#endif _singlemouseeventmanager
#pragma once
