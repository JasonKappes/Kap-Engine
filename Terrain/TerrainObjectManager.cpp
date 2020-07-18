#include "TerrainObjectManager.h"
#include "TerrainLoader.h"
#include "TerrainObject.h"

TerrainObjectManager::TerrainObjectManager() : terrainObject(nullptr) {}

void TerrainObjectManager::EnableTerrain(const char* filename)
{
	terrainObject = TerrainLoader::Get(filename);
	terrainObject->SceneEntry();
}

void TerrainObjectManager::DisableTerrain()
{
	terrainObject->SceneExit();
}

TerrainObject* TerrainObjectManager::GetTerrainObject()
{
	return terrainObject;
}