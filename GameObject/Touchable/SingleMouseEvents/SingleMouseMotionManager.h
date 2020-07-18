#ifndef _singlemousemotionmanager
#define _singlemousemotionmanager
#include <AzulCore.h>
#include "EventType.h"
#include <unordered_set>
#include "SingleMouseEventManager.h"

class Touchable;

class SingleMouseMotionManager : public SingleMouseEventManager
{
public:
	using TouchSet = std::unordered_set<Touchable*>;
	using KeyStorageRef = TouchSet::iterator;
	using MousePosition = std::pair<float, float>;

private:
	enum class LASTFRAME_STATUS { PRESSED, RELEASED };

public: // ---> ENGINE METHODS
	SingleMouseMotionManager() = delete;
	SingleMouseMotionManager(AZUL_MOUSE);
	SingleMouseMotionManager(const SingleMouseMotionManager&) = delete;
	SingleMouseMotionManager operator=(const SingleMouseMotionManager&) = delete;
	~SingleMouseMotionManager() { DebugMsg::out(" \n SINGLE MOUSE MOTION MANAGER Destructor "); }

	void ProcessMouseEvent() override;
	bool MouseMovement();

	void TriggerMouseDirection();

	void RegisterTouchable(Touchable*, MOUSE_EVENT_TYPE e, KeyStorageRef&) override;
	void DeRegisterTouchable(MOUSE_EVENT_TYPE e, KeyStorageRef&) override;

private:
	AZUL_MOUSE m_direction;
	TouchSet m_mouseDirectionCol;
	MousePosition pastMousePosition;
};

#endif _singlemousemotionmanager
#pragma once
