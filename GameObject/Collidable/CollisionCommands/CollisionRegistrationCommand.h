#ifndef _collisionregistrationcommand
#define _collisionregistrationcommand
#include "SceneRegistrationCommand.h"

class Collidable;

class CollisionRegistrationCommand : public SceneRegistrationCommand
{
public:
	CollisionRegistrationCommand() = delete;
	CollisionRegistrationCommand(Collidable*);
	CollisionRegistrationCommand(const CollisionRegistrationCommand&) = delete;
	CollisionRegistrationCommand operator=(const CollisionRegistrationCommand&) = delete;
	~CollisionRegistrationCommand() = default;

protected:
	void Execute() override;

private:
	Collidable* m_collidable;
};

#endif _collisionregistrationcommand
#pragma once
