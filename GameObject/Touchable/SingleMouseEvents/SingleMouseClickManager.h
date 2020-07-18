#ifndef _singlemouseclickmanager
#define _singlemouseclickmanager
#include <unordered_set>
#include "SingleMouseEventManager.h"

class Touchable;

class SingleMouseClickManager : public SingleMouseEventManager
{
private:
	enum class LASTFRAME_STATUS { PRESSED, RELEASED };

public: // ---> ENGINE METHODS
	SingleMouseClickManager() = delete;
	SingleMouseClickManager(AZUL_MOUSE);
	SingleMouseClickManager(const SingleMouseClickManager&) = delete;
	SingleMouseClickManager operator=(const SingleMouseClickManager&) = delete;
	~SingleMouseClickManager() { DebugMsg::out(" \n SINGLE MOUSE CLICK MANAGER Destructor "); }

	void ProcessMouseEvent() override;

	void RegisterTouchable(Touchable*, MOUSE_EVENT_TYPE e, KeyStorageRef&) override;
	void DeRegisterTouchable(MOUSE_EVENT_TYPE e, KeyStorageRef&) override;

	void TriggerMousePress();
	void TriggerMouseHeld();
	void TriggerMouseRelease();

private:
	AZUL_MOUSE m_key;
	TouchSet m_mouseHeldDownCol;
	TouchSet m_mousePressedCol;
	TouchSet m_mouseReleasedCol;
	LASTFRAME_STATUS m_lastFrameState;
};

#endif _singlemouseclickmanager
#pragma once
