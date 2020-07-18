#include "CollisionTestPairCommand.h"
#include "CollidableDispatchBase.h"
#include "CollisionVolumeBSphere.h"
#include "CollidableGroup.h"
#include "CollisionVolumeAABB.h"
#include "CollidableDispatch.h"
#include "CollidableAttorney.h"
#include "KapMathTools.h"
#include "VisualizerAttorney.h"
#include "Color.h"
#include "SceneAttorney.h"

CollisionTestPairCommand::CollisionTestPairCommand(CollidableGroup* t_cg1, CollidableGroup* t_cg2, CollidableDispatchBase* t_collDispatch)
{
	this->m_collidableGroup1 = t_cg1;
	this->m_collidableGroup2 = t_cg2;
    this->m_collidableDispatch = t_collDispatch;
}

CollisionTestPairCommand::~CollisionTestPairCommand()
{
    delete this->m_collidableDispatch;
}

void CollisionTestPairCommand::Execute()
{
    const CollidableGroup::CollidableCollection& Collection1 = m_collidableGroup1->GetColliderCollection();
    const CollidableGroup::CollidableCollection& Collection2 = m_collidableGroup2->GetColliderCollection();

    if (!Collection1.empty() && !Collection2.empty())
    {
        //Test Collidable group AABB
        if (KapMathTools::Intersect(m_collidableGroup1->GetGroupVolume(), m_collidableGroup2->GetGroupVolume()))
        {
            //Test BSphere against group AABB
            if (GroupBSphereCheck(Collection1, *m_collidableGroup2) || GroupBSphereCheck(Collection2, *m_collidableGroup1))
            {
                //Test individual instances
                IndividualInstanceCheck(Collection1, Collection2);
            }

            //m_collidableGroup1->GetGroupVolume().DebugView(Color::Red);
           // m_collidableGroup2->GetGroupVolume().DebugView(Color::Red);
        }
        else {
           // m_collidableGroup1->GetGroupVolume().DebugView(Color::Green);
           //m_collidableGroup2->GetGroupVolume().DebugView(Color::Green);
        }
    }
}

bool CollisionTestPairCommand::GroupBSphereCheck(const CollidableGroup::CollidableCollection& collection, CollidableGroup& group) const
{
    const CollisionVolumeAABB& groupaabb = group.GetGroupVolume();

    for (auto it1 = collection.begin(); it1 != collection.end(); it1++)
    {
        Collidable& collRef = **it1;
        const CollisionVolume& bs1 = CollidableAttorney::Collision::GetDefaultBSphere(collRef);

        if (groupaabb.IntersectAccept(bs1))
        {
            return true;
        }
    }
    return false;
}

bool CollisionTestPairCommand::GroupAABBObjectCheck(const CollidableGroup::CollidableCollection& collection, CollidableGroup& group) const
{
    const CollisionVolumeAABB& groupaabb = group.GetGroupVolume();

    for (auto it1 = collection.begin(); it1 != collection.end(); it1++)
    {
        Collidable& collRef = **it1;
        const CollisionVolume& bs1 = CollidableAttorney::Collision::GetCollisionVolume(collRef);

        if (groupaabb.IntersectAccept(bs1))
        {
            return true;
        }
    }
    return false;
}

void CollisionTestPairCommand::IndividualInstanceCheck(const CollidableGroup::CollidableCollection& Collection1, const CollidableGroup::CollidableCollection& Collection2)
{
    for (auto it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
    {
        Collidable& outer_collidableRef = **it1;
        const CollisionVolumeBSphere& bsphere1 = CollidableAttorney::Collision::GetDefaultBSphere(outer_collidableRef);
        for (auto it2 = Collection2.begin(); it2 != Collection2.end(); it2++)
        {
            Collidable& inner_collidableRef = **it2;
            const CollisionVolumeBSphere& bsphere2 = CollidableAttorney::Collision::GetDefaultBSphere(inner_collidableRef);

            //Test individual BSpheres
            if (KapMathTools::Intersect(bsphere1, bsphere2))
            {
              // bsphere1.DebugView(Color::Red);
              // bsphere2.DebugView(Color::Red);

                const CollisionVolume& volume1 = CollidableAttorney::Collision::GetCollisionVolume(outer_collidableRef);
                const CollisionVolume& volume2 = CollidableAttorney::Collision::GetCollisionVolume(inner_collidableRef);

                //Test individual volumes
                if (KapMathTools::Intersect(volume1, volume2))
                {
                    this->m_collidableDispatch->ProcessCallbacks(*it1, *it2);

                   // volume1.DebugView(Color::Black);
                   // volume2.DebugView(Color::Black);
                }
                else {
                    //volume1.DebugView(Color::Blue);
                   // volume2.DebugView(Color::Blue);
                }
            }
            else {
               // bsphere1.DebugView(Color::Blue);
               // bsphere2.DebugView(Color::Blue);
            }
        }
    }
}
