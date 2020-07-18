#ifndef _collisiontestpaircommand
#define _collisiontestpaircommand
#include "CollisionTestCommandBase.h"
#include "CollidableGroup.h"

class CollidableDispatchBase;
class CollisionVolumeAABB;

class CollisionTestPairCommand : public CollisionTestCommandBase
{
public:
	CollisionTestPairCommand() = delete;
	CollisionTestPairCommand(CollidableGroup*, CollidableGroup*, CollidableDispatchBase*);
	CollisionTestPairCommand(const CollisionTestPairCommand&) = delete;
	CollisionTestPairCommand operator=(const CollisionTestPairCommand&) = delete;
	~CollisionTestPairCommand();

protected:
	void Execute() override;

private:
	bool GroupAABBObjectCheck(const CollidableGroup::CollidableCollection&, CollidableGroup&) const;
	bool GroupBSphereCheck(const CollidableGroup::CollidableCollection&, CollidableGroup&) const;
	void IndividualInstanceCheck(const CollidableGroup::CollidableCollection&, const CollidableGroup::CollidableCollection&);

private:
	CollidableGroup* m_collidableGroup1;
	CollidableGroup* m_collidableGroup2;
	CollidableDispatchBase* m_collidableDispatch;
};

#endif _collisiontestpaircommand
#pragma once
