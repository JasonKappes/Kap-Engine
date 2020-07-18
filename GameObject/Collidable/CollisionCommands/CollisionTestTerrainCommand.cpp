#include "CollisionTestTerrainCommand.h"
#include "CollidableGroup.h"
#include "CollisionVolume.h"
#include "CollidableAttorney.h"
#include "TerrainRectangleArea.h"
#include "TerrainObject.h"
#include "TRAIterator.h"
#include "KapMathTools.h"
#include "Scene.h"
#include "CollisionVolumeAABB.h"
#include "VisualizerAttorney.h"
#include "CollisionVolumeBSphere.h"

CollisionTestTerrainCommand::CollisionTestTerrainCommand(CollidableGroup* c1, CollidableDispatchBase* disp)
{
    m_collidableGroup1 = c1;
    m_collidableDispatch = disp;
}

CollisionTestTerrainCommand::~CollisionTestTerrainCommand()
{
    delete this->m_collidableDispatch;
}

void CollisionTestTerrainCommand::Execute()
{
    const CollidableGroup::CollidableCollection& Collection1 = m_collidableGroup1->GetColliderCollection();

    if (!Collection1.empty())
    {

        //Cycle through collidable instances
        for (auto it = Collection1.begin(); it != Collection1.end(); ++it)
        {
            //get collidable default bsphere
            Collidable& collidableRef = **it;
            const CollisionVolumeBSphere& defaultBSphere = CollidableAttorney::Collision::GetDefaultBSphere(collidableRef);

            TerrainObject* sceneTerrain = SceneManager::GetCurrentScene()->GetTerrain();

            //Test if the volume is within the terrain
            if (!sceneTerrain->ObjectWithinTerrain(defaultBSphere.GetCenter(), (int)defaultBSphere.GetRadius())) break;

            //If the volume is within the terrain, get the collision area
            TerrainRectangleArea* CollisionCollection = sceneTerrain->GetCollisionArea(defaultBSphere.GetCenter(), defaultBSphere.GetRadius());

            TRAIterator cellIt(CollisionCollection);

            //check intersection in terrain collision area versus instance
            for (cellIt = CollisionCollection->begin(); cellIt != CollisionCollection->end(); ++cellIt)
            {
                const CollisionVolume& cellVol = *cellIt.GetVolume();

                CellIntersectionTest(collidableRef, cellVol);
            }

            const CollisionVolume& cellVol = *cellIt.GetVolume();

            CellIntersectionTest(collidableRef, cellVol);

            delete CollisionCollection;
        }
    }
}

void CollisionTestTerrainCommand::CellIntersectionTest(Collidable& collidableRef, const CollisionVolume& cellVol)
{
    const CollisionVolumeBSphere& defaultBSphere = CollidableAttorney::Collision::GetDefaultBSphere(collidableRef);

    if (KapMathTools::Intersect(cellVol, defaultBSphere))
    {
        //defaultBSphere.DebugView(Color::Red);

        const CollisionVolume& collidableVol = CollidableAttorney::Collision::GetCollisionVolume(collidableRef);
        if (KapMathTools::Intersect(cellVol, collidableVol))
        {
            m_collidableDispatch->ProcessCallbacks(&collidableRef);
            cellVol.DebugView(Vect(1.0f, 0.0f, 0.0f));
            collidableVol.DebugView(Vect(1.0f, 0.0f, 0.0f));
        }
        else {
            cellVol.DebugView(Vect(0.0f, 0.0f, 1.0f));
            collidableVol.DebugView(Vect(0.0f, 0.0f, 1.0f));
        }
    }
    else {
        //defaultBSphere.DebugView(Color::Blue);
    }
}
