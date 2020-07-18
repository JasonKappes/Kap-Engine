#ifndef _collidablegroup
#define _collidablegroup
#include <list>
#include <DebugOut.h>
#include "Align16.h"
#include "Matrix.h"

class Collidable;
class CollisionVolumeAABB;

class CollidableGroup : public Align16
{
public:
	using CollidableCollection = std::list<Collidable*>;
	using CollidableCollectionRef = CollidableCollection::iterator;

public:
	void DeRegister(const CollidableCollectionRef&);
	void Register(Collidable*, CollidableCollectionRef&);
	const CollidableCollection& GetColliderCollection();
	void CalculateGroupAABB();

	const CollisionVolumeAABB& GetGroupVolume();

	void VisualizeCollidableMembers() const;

public:
	CollidableGroup();
	CollidableGroup(const CollidableGroup&) = delete;
	CollidableGroup operator=(const CollidableGroup&) = delete;
	~CollidableGroup();

private:
	std::list<Collidable*> m_CollidableCol;
	CollisionVolumeAABB* m_groupAABB;

	Vect volumeColor;
	Vect min;
	Vect max;
	Vect scale;
	Vect trans;
	Matrix world;


};

#endif _collidablegroup
#pragma once
