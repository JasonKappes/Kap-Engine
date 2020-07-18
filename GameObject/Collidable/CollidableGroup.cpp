#include "CollidableGroup.h"
#include <DebugOut.h>
#include "Collidable.h"
#include "VisualizerAttorney.h"
#include "Color.h"
#include "CollisionVolumeAABB.h"
#include "CollidableAttorney.h"
#include "CollisionVolume.h"

CollidableGroup::CollidableGroup()
{
	this->m_groupAABB = new CollisionVolumeAABB();
	volumeColor = Color::Green;
}

void CollidableGroup::DeRegister(const CollidableCollectionRef& t_ref)
{
	DebugMsg::out("\n COLLIDABLE GROUP size: %d ----> de-register ", this->m_CollidableCol.size());
	this->m_CollidableCol.erase(t_ref);
}

void CollidableGroup::Register(Collidable* t_collidable, CollidableCollectionRef& t_ref)
{
	DebugMsg::out("\n COLLIDABLE GROUP ----> register  IND: COLLIDABLE SIZE: %d ", this->m_CollidableCol.size());
	t_ref = this->m_CollidableCol.insert(this->m_CollidableCol.begin(), t_collidable);
}

const CollidableGroup::CollidableCollection& CollidableGroup::GetColliderCollection()
{
	return this->m_CollidableCol;
}

void CollidableGroup::CalculateGroupAABB()
{
	if (!this->m_CollidableCol.empty())
	{
		//Get first elements min/max
		Vect firstCenter = CollidableAttorney::GameLoop::GetCenter(**this->m_CollidableCol.begin());
		float firstRadius = CollidableAttorney::GameLoop::GetRadius(**this->m_CollidableCol.begin());

		float maxx = firstCenter.X() + firstRadius;
		float maxy = firstCenter.Y() + firstRadius;
		float maxz = firstCenter.Z() + firstRadius;

		float minx = firstCenter.X() - firstRadius;
		float miny = firstCenter.Y() - firstRadius;
		float minz = firstCenter.Z() - firstRadius;

		float tmpminx, tmpmaxx, tmpminy, tmpmaxy, tmpminz, tmpmaxz;

		//get the best min/max versus the rest of the elements
		if (this->m_CollidableCol.size() > 1)
		{
			CollidableCollectionRef it = this->m_CollidableCol.begin();
			it++;
			for (it; it != this->m_CollidableCol.end(); ++it)
			{
				Vect center = CollidableAttorney::GameLoop::GetCenter((**it));
				float radius = CollidableAttorney::GameLoop::GetRadius((**it));

				tmpminx = center.X() - radius;
				tmpmaxx = center.X() + radius;
				tmpminy = center.Y() - radius;
				tmpmaxy = center.Y() + radius;
				tmpminz = center.Z() - radius;
				tmpmaxz = center.Z() + radius;

				if (tmpmaxx > maxx)		maxx = tmpmaxx;
				if (tmpminx < minx)  minx = tmpminx;

				if (tmpmaxy > maxy)		maxy = tmpmaxy;
				if (tmpminy < miny)  miny = tmpminy;

				if (tmpmaxz > maxz)		maxz = tmpmaxz;
				if (tmpminz < minz)  minz = tmpminz;
			}
		}

		this->min = Vect(minx, miny, minz);
		this->m_groupAABB->SetMin(min);

		this->max = Vect(maxx, maxy, maxz);
		this->m_groupAABB->SetMax(max);

		this->scale = Vect(maxx - minx, maxy - miny, maxz - minz);
		this->m_groupAABB->SetScale(scale);

		this->trans = 0.5f * (min + max);
		this->m_groupAABB->SetTrans(trans);

	}
}

const CollisionVolumeAABB& CollidableGroup::GetGroupVolume() 
{
	return *this->m_groupAABB;
}

void CollidableGroup::VisualizeCollidableMembers() const
{
	if (!this->m_CollidableCol.empty())
	{
		CollidableGroup::CollidableCollection::const_iterator it = this->m_CollidableCol.begin();
		while (it != this->m_CollidableCol.end())
		{
			CollidableAttorney::Collision::GetCollisionVolume(**it).DebugView(Color::Green);
			++it;
		}
	}
}

CollidableGroup::~CollidableGroup()
{
	this->m_CollidableCol.clear();
	delete this->m_groupAABB;
	DebugMsg::out("\n COLLIDABLE GROUP DESTRUCTOR, size: %d ", this->m_CollidableCol.size());
}
