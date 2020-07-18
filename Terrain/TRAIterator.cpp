#include "TRAIterator.h"
#include "TerrainRectangleArea.h"
#include "CollisionVolumeAABB.h"

TRAIterator::TRAIterator(TerrainRectangleArea* tra)
{
	this->area = tra;
}

void TRAIterator::operator++()
{
	//might be a nullptr
	this->volume = &this->area->GetNextCell();
}

bool TRAIterator::operator!=(const CollisionVolumeAABB& endvolume)
{
	//If we're not at end, we're in the clear
	if (*this->volume == endvolume) return false;
	return true;
}

void TRAIterator::operator=(const CollisionVolumeAABB& beginvolume)
{
	this->volume = &beginvolume;
}

const CollisionVolumeAABB* TRAIterator::GetVolume()
{
	return volume;
}

void TRAIterator::SetCollisionArea(TerrainRectangleArea* terrain)
{
	this->area = terrain;
}
