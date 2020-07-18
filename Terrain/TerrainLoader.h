#ifndef _terrainloader
#define _terrainloader
#include <map>

class TerrainObject;

class TerrainLoader
{
	friend class TerrainLoaderAttorney;
public:
	static void Load(const char* filename, const char* filepath, const char* texture,
		float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
	{
		Instance().privLoad(filename, filepath, texture, len, maxheight, ytrans, RepeatU, RepeatV);
	}

	static TerrainObject* Get(const char* filename) { return Instance().privGet(filename); }

public:
	/// <summary>
	/// A default model to load is a frigate. Load this model (to use for a GameObject) in LoadAllResources.cpp.
	/// 
	/// Default Key Syntax: 	ModelManager::Load("DefaultAssets/space_frigate.azul");
	/// </summary> 
	/// \ingroup ModelManager
	static std::string defaultAssetKey;

private:
	TerrainLoader() = default;
	TerrainLoader(const TerrainLoader&) = delete;
	TerrainLoader operator=(const TerrainLoader&) = delete;
	~TerrainLoader();

	static TerrainLoader& Instance()
	{
		if (!ptrInstance)
		{
			ptrInstance = new TerrainLoader();
		}
		return *ptrInstance;
	}

	void privLoad(const char* filename, const char* filepath, const char* texture,
		float len, float maxheight, float ytrans, int RepeatU, int RepeatV);

	TerrainObject* privGet(const char* filename);

	static void Terminate();

private:
	static TerrainLoader* ptrInstance;
	typedef std::map<std::string, TerrainObject*> terrainMap;
	terrainMap m_terrainMap;
};

#endif _terrainloader
#pragma once
