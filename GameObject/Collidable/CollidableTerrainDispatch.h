#ifndef _collidableterraindispatch
#define _collidableterraindispatch
#include "CollidableDispatchBase.h"

template <typename C1>
class CollidableTerrainDispatch : public CollidableDispatchBase
{
public:
    CollidableTerrainDispatch() = default;
    CollidableTerrainDispatch(const CollidableTerrainDispatch&) = delete;
    CollidableTerrainDispatch operator=(const CollidableTerrainDispatch&) = delete;
    ~CollidableTerrainDispatch() = default;

    virtual void ProcessCallbacks(Collidable* c1)
    {
        C1* pDerCol1 = static_cast<C1*>(c1);

        pDerCol1->CollisionTerrain();
    }
};

#endif _collidableterraindispatch
#pragma once
