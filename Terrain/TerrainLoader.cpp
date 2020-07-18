#include "TerrainLoader.h"
#include "TerrainObject.h"

TerrainLoader* TerrainLoader::ptrInstance = nullptr;

std::string TerrainLoader::defaultAssetKey = "DefaultAssets/HMtest.tga";

void TerrainLoader::privLoad(const char* filename, const char* filepath, const char* texture, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	try
	{
		if (this->m_terrainMap.at(filename) != NULL) { 		//check if terrain has been added
			throw std::runtime_error(" ERROR: Duplicate Terrain (ID: " + (std::string)filename + ") loaded. ");
		}
	}
	catch (std::out_of_range exc) {							// if not, then add it

		this->m_terrainMap[filename] = new TerrainObject(filepath, texture, len, maxheight, ytrans, RepeatU, RepeatV);
		return;
	}
	return;
}

TerrainObject* TerrainLoader::privGet(const char* filename)
{
	try
	{
		return this->m_terrainMap.at(filename);			//return terrain, if it is valid
	}
	catch (std::out_of_range exc)						// if not, throw
	{
		throw std::runtime_error(" ERROR: Terrain (ID: " + (std::string) filename + ") not found. ");
	}
}

TerrainLoader::~TerrainLoader()
{
	terrainMap::iterator it;

	for (it = this->m_terrainMap.begin(); it != this->m_terrainMap.end(); ++it)
	{
		delete it->second;
	}

	this->m_terrainMap.clear();

	DebugMsg::out(" \n Terrain Loader: size: %d ", this->m_terrainMap.size());
}

void TerrainLoader::Terminate()
{
	delete Instance().ptrInstance;
}

