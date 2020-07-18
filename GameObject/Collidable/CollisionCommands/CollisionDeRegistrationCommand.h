#ifndef _collisionderegistrationcommand
#define _collisionderegistrationcommand
#include "SceneRegistrationCommand.h"

class Collidable;

class CollisionDeRegistrationCommand : public SceneRegistrationCommand
{
public:
	CollisionDeRegistrationCommand() = delete;
	CollisionDeRegistrationCommand(Collidable*);
	CollisionDeRegistrationCommand(const CollisionDeRegistrationCommand&) = delete;
	CollisionDeRegistrationCommand operator=(const CollisionDeRegistrationCommand&) = delete;
	~CollisionDeRegistrationCommand() = default;

protected:
	void Execute() override;

private:
	Collidable* m_collidable;
};

#endif _collisionderegistrationcommand
#pragma once
