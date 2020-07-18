#ifndef _collisiontestterraincommand
#define _collisiontestterraincommand
#include "CollisionTestCommandBase.h"

class CollidableDispatchBase;
class CollidableGroup;
class Collidable;
class CollisionVolume;

class CollisionTestTerrainCommand : public CollisionTestCommandBase
{
public:
	CollisionTestTerrainCommand() = default;
	CollisionTestTerrainCommand(const CollisionTestTerrainCommand&) = delete;
	CollisionTestTerrainCommand operator=(const CollisionTestTerrainCommand&) = delete;
	~CollisionTestTerrainCommand();

	CollisionTestTerrainCommand(CollidableGroup*, CollidableDispatchBase*);

	void Execute() override;

private:
	void CellIntersectionTest(Collidable& obj, const CollisionVolume&);

private:
	CollidableGroup* m_collidableGroup1;
	CollidableDispatchBase* m_collidableDispatch;

};

#endif _collisiontestterraincommand
#pragma once
