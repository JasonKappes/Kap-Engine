#ifndef _terrainloaderattorney
#define _terrainloaderattorney
#include "TerrainLoader.h"

class TerrainLoaderAttorney
{
	friend class KapEngine;
private:
	static void Delete() { TerrainLoader::Terminate(); }

private:
	TerrainLoaderAttorney() = delete;
	TerrainLoaderAttorney(const TerrainLoaderAttorney&) = delete;
	TerrainLoaderAttorney operator=(const TerrainLoaderAttorney&) = delete;
	~TerrainLoaderAttorney() = delete;
};

#endif _terrainloaderattorney
#pragma once
