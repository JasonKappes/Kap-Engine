#include "GameUpdate.h"
#include "KeyboardEventManager.h"
#include "MouseEventManager.h"
#include "AlarmableManager.h"
#include "UpdatableManager.h"
#include "CollidableManager.h"
#include "SceneRegistrationBroker.h"

void GameUpdate::Tick() const
{
	this->m_RegistrationBroker->ExecuteCommands();

	this->m_AlarmableManager->ProcessAlarms();

	this->m_KeyboardEventManager->ProcessSingleKeyEvents();

	this->m_MouseEventManager->ProcessSingleMouseEvents();

	this->m_UpdatableManager->ProcessUpdates();

	this->m_CollidableManager->ProcessCollisions();

	this->m_UpdatableManager->ProcessLateUpdates();
}

GameUpdate::GameUpdate(const KeyboardEventManager& km, SceneRegistrationBroker* sm, const UpdatableManager& um, const CollidableManager& cm, AlarmableManager* am, const MouseEventManager& mm)
{
	this->m_RegistrationBroker		= sm;

	this->m_AlarmableManager		= am;

	this->m_KeyboardEventManager	= &km;

	this->m_MouseEventManager		= &mm;

	this->m_UpdatableManager		= &um;

	this->m_CollidableManager		= &cm;
}

