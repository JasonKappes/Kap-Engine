#include "MouseEventManager.h"
#include "SingleMouseClickManager.h"
#include "SingleMouseMotionManager.h"

MouseEventManager::MouseEventManager() : m_singleMouseAction(nullptr) { }

MouseEventManager::~MouseEventManager()
{
	auto singleMouseActionManager = this->m_timeLine.begin();
	while (singleMouseActionManager != this->m_timeLine.end())
	{
		delete singleMouseActionManager->second;
		this->m_timeLine.erase(singleMouseActionManager++);
	}

	DebugMsg::out("\n MouseEventEventManager destructor: SingleMouseActionCollection ------ > size: %d ", this->m_timeLine.size());
}

void MouseEventManager::ProcessSingleMouseEvents() const
{
	for (auto keyEvent : this->m_timeLine)
		keyEvent.second->ProcessMouseEvent();
}

void MouseEventManager::RegisterSingleMouseAction(Touchable* t_touchable, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event, SingleMouseEventManager::KeyStorageRef& t_iterator)
{
	if (this->m_timeLine.find(t_key) == this->m_timeLine.end()) //check for key... if does not exist, create a new key
	{
		DebugMsg::out("\n KeyBoardEventManager: REGISTERED new single key manager \n");
		if (t_key < AZUL_MOUSE::CURSOR_MOVEMENT_LEFT) //single mouse clicks
		{
			this->m_timeLine.insert(singleMouseEventMap::value_type(t_key, new SingleMouseClickManager(t_key)));
		}
		else if(t_key >= AZUL_MOUSE::CURSOR_MOVEMENT_LEFT && t_key <= AZUL_MOUSE::CURSOR_MOVEMENT_DOWN) //singel dir
		{
			this->m_timeLine.insert(singleMouseEventMap::value_type(t_key, new SingleMouseMotionManager(t_key)));
		}
	}

	//register new GO to singleKeyManager
	this->m_timeLine[t_key]->RegisterTouchable(t_touchable, t_event, t_iterator);
}

void MouseEventManager::DeRegisterSingleMouseAction(AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event, SingleMouseEventManager::KeyStorageRef& t_iterator)
{
	DebugMsg::out("\n MouseEventManager: DE-REGISTERED a single mouse action manager \n");

	assert(this->m_timeLine.size() > 0);

	this->m_timeLine[t_key]->DeRegisterTouchable(t_event, t_iterator);
}
