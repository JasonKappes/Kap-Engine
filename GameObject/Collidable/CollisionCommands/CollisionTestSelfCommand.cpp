#include "CollisionTestSelfCommand.h"
#include "CollidableDispatchBase.h"
#include "CollisionVolumeBSphere.h"
#include "KapMathTools.h"
#include "VisualizerAttorney.h"
#include "Color.h"
#include "CollidableGroup.h"
#include "CollidableAttorney.h"

CollisionTestSelfCommand::CollisionTestSelfCommand(CollidableGroup* t_colGroup, CollidableDispatchBase* t_colDispatchBase)
{
	this->m_collidableGroup1 = t_colGroup;
    this->m_collidableDispatch = t_colDispatchBase;
}

CollisionTestSelfCommand::~CollisionTestSelfCommand()
{
    delete this->m_collidableDispatch;
}

void CollisionTestSelfCommand::Execute()
{
    const CollidableGroup::CollidableCollection& Collection1 = m_collidableGroup1->GetColliderCollection();

    CollidableGroup::CollidableCollection::const_iterator it1;
    CollidableGroup::CollidableCollection::const_iterator it2;

    for (it1 = Collection1.begin(); it1 != Collection1.end(); it1++)
    {
        Collidable& outer_collidableRef = **it1;

        const CollisionVolume& defaultsphere1 = CollidableAttorney::Collision::GetDefaultBSphere(outer_collidableRef);
        it2 = it1;
        for (it2 = ++it2; it2 != Collection1.end(); it2++)
        {
            Collidable& inner_collidableRef = **it2;

            const CollisionVolume& defaultsphere2 = CollidableAttorney::Collision::GetDefaultBSphere(inner_collidableRef);
            if (KapMathTools::Intersect(defaultsphere1, defaultsphere2))
            {
                const CollisionVolume& volume1 = CollidableAttorney::Collision::GetCollisionVolume(outer_collidableRef);
                const CollisionVolume& volume2 = CollidableAttorney::Collision::GetCollisionVolume(inner_collidableRef);

                if (KapMathTools::Intersect(volume1, volume2))
                {
                    this->m_collidableDispatch->ProcessCallbacks(*it1, *it2);
                    volume1.DebugView(Color::Red);
                    volume2.DebugView(Color::Red);
                }
                else {
                    volume1.DebugView(Color::Blue);
                    volume2.DebugView(Color::Blue);
                }
            }
            else {
                defaultsphere1.DebugView(Color::Blue);
                defaultsphere2.DebugView(Color::Blue);
            }
        }
    }
}
