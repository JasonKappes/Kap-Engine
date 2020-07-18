#ifndef _terrainobjectmanager
#define _terrainobjectmanager
#include <map>

class TerrainObject;

class TerrainObjectManager
{
public:
	TerrainObjectManager();
	TerrainObjectManager(const TerrainObjectManager&) = delete;
	TerrainObjectManager operator=(const TerrainObjectManager&) = delete;
	~TerrainObjectManager() = default;

	void EnableTerrain(const char* filename);

	void DisableTerrain();

	TerrainObject* GetTerrainObject();

private:

	TerrainObject* terrainObject;
};

#endif _terrainobjectmanager
#pragma once
