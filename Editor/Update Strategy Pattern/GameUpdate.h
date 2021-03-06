#ifndef _gameupdate
#define _gameupdate
#include "SystemUpdate.h"

class KeyboardEventManager;
class MouseEventManager;
class SceneRegistrationBroker;
class AlarmableManager;
class UpdatableManager;
class CollidableManager;

//(Strategy Pattern Object): This defines what systems are being updated while the game (not world-edit mode) is running
class GameUpdate : public SystemUpdate
{
public:
	GameUpdate() = delete;
	GameUpdate(const GameUpdate&) = delete;
	GameUpdate operator=(const GameUpdate&) = delete;
	~GameUpdate() = default;

	GameUpdate(const KeyboardEventManager&, SceneRegistrationBroker*, const UpdatableManager&,
		const CollidableManager&, AlarmableManager*, const MouseEventManager&);

protected:
	//Looks for Keyboard and mouse events, updates objects, checks for collisions, registers alarms
	void Tick() const override;

private:
	const KeyboardEventManager*		m_KeyboardEventManager;
	const MouseEventManager*			m_MouseEventManager;
	const UpdatableManager*			m_UpdatableManager;
	const CollidableManager*			m_CollidableManager;\

	SceneRegistrationBroker* m_RegistrationBroker;
	AlarmableManager*			m_AlarmableManager;

};
#endif _gameupdate
#pragma once
