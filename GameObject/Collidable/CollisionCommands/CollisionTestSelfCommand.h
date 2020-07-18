#ifndef _collisiontestselfcommand
#define _collisiontestselfcommand
#include "CollisionTestCommandBase.h"

class Collidable;
class CollidableGroup;
class CollidableDispatchBase;

class CollisionTestSelfCommand : public CollisionTestCommandBase
{
public:
	CollisionTestSelfCommand() = delete;
	CollisionTestSelfCommand(CollidableGroup*, CollidableDispatchBase*);
	CollisionTestSelfCommand(const CollisionTestSelfCommand&) = delete;
	CollisionTestSelfCommand operator=(const CollisionTestSelfCommand&) = delete;
	~CollisionTestSelfCommand();

protected:
	void Execute() override;

private:
	CollidableGroup* m_collidableGroup1;
	CollidableDispatchBase* m_collidableDispatch;
};

#endif _collisiontestselfcommand
#pragma once
