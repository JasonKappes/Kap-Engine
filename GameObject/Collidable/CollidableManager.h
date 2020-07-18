#ifndef _collidablemanager
#define _collidablemanager
#include <vector>
#include <list>
#include <DebugOut.h>
#include "CollisionTestSelfCommand.h"
#include "CollisionTestPairCommand.h"
#include "CollisionTestTerrainCommand.h"
#include "CollisionTestTerrainCommand.h"
#include "CollidableDispatch.h"
#include "CollidableTerrainDispatch.h"

class CollidableGroup;
class CollisionTestCommandBase;
class CollidableDispatchBase;
class Collidable;

class CollidableManager
{
public:
    using PWTypeID = int;

private:
    using CollidableGroupCollection = std::vector<CollidableGroup*>;
    using CollisionTestCommands = std::list<CollisionTestCommandBase*>;

public:
    CollidableManager() {
        float vectorStartingSize = 500;
        TypeIDNextNumber = 0;
        for (int x = 0; x < vectorStartingSize; ++x) {
            this->m_CollidableGroupCol.push_back(nullptr);
        }
    };
    CollidableManager(const CollidableManager&) = delete;
    CollidableManager operator=(const CollidableManager&) = delete;
    ~CollidableManager();

    CollidableGroup* GetCollisionGroup(CollidableManager::PWTypeID);

    void ProcessCollisions() const;

    void VisualizeAllVolumes();

public:
    static const PWTypeID PWID_UNDEFINED = -1;

private:
    static PWTypeID TypeIDNextNumber;
    CollidableGroupCollection m_CollidableGroupCol;
    CollisionTestCommands m_colTestCommands;

private:
    void SetGroupForTypeID(CollidableManager::PWTypeID);

public:
    template <typename C1>
    void SetCollisionTerrain()
    {
        CollidableGroup* pg1 = m_CollidableGroupCol[GetInstanceID<C1>()];

        CollidableTerrainDispatch<C1>* pDispatch = new CollidableTerrainDispatch<C1>();

        this->m_colTestCommands.push_back(new CollisionTestTerrainCommand(pg1, pDispatch));
    }

    template< typename C1, typename C2>
    void SetCollisionPair()
    {
        CollidableGroup* pg1 = m_CollidableGroupCol[GetInstanceID<C1>()];
        CollidableGroup* pg2 = m_CollidableGroupCol[GetInstanceID<C2>()];

        CollidableDispatch<C1, C2>* pDispatch = new CollidableDispatch<C1, C2>();
        
        this->m_colTestCommands.push_back(new CollisionTestPairCommand(pg1, pg2, pDispatch));
    }

    template< typename C1>
    void SetCollisionSelf()
    {
        CollidableGroup* pg1 = m_CollidableGroupCol[GetInstanceID<C1>()];

        CollidableDispatch<C1, C1>* pDispatch = new CollidableDispatch<C1, C1>();

        DebugMsg::out("\n COLLIDABLE MANAGER: new collision group test-self pushed ");

        this->m_colTestCommands.push_back(new CollisionTestSelfCommand(pg1, pDispatch));
    }

    template <typename C>
    PWTypeID GetInstanceID()
    {
        static PWTypeID myTypeID = TypeIDNextNumber++;

        SetGroupForTypeID(myTypeID);

        DebugMsg::out("\n COLLIDABLE MANAGER: Type ID: %i\n", myTypeID);
        return myTypeID;
    }


};

#endif _collidablemanager
#pragma once
