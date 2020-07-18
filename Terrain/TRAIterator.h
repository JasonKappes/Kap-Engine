#ifndef _TRAIterator
#define _TRAIterator

class CollisionVolumeAABB;
class TerrainRectangleArea;

class TRAIterator
{
public:
	TRAIterator() = default;
	TRAIterator(const TRAIterator&) = delete;
	TRAIterator operator=(const TRAIterator&) = delete;
	~TRAIterator() = default;

	TRAIterator(TerrainRectangleArea*);

	void TRAIterator::operator++();

	bool operator!=(const CollisionVolumeAABB&);

	void operator=(const CollisionVolumeAABB&);

	const CollisionVolumeAABB* GetVolume();

	void SetCollisionArea(TerrainRectangleArea*);

private:
	TerrainRectangleArea* area;
	const CollisionVolumeAABB* volume;
};

#endif _TRAIterator
#pragma once
