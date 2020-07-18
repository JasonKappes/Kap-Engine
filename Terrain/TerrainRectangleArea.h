#ifndef _terrainrectanglearea
#define _terrainrectanglearea

class TRAIterator;
class CollisionVolumeAABB;
class TerrainObject;

class TerrainRectangleArea
{
public:
	TerrainRectangleArea() = delete;
	TerrainRectangleArea(const TerrainRectangleArea&) = delete;
	TerrainRectangleArea operator=(const TerrainRectangleArea&) = delete;
	~TerrainRectangleArea() = default;

	TerrainRectangleArea(TerrainObject* terrain, float terrainLength, int startRow, int endRow, int startCol, int endCol);

	const CollisionVolumeAABB& GetNextCell();

	const CollisionVolumeAABB& begin();

	const CollisionVolumeAABB& end();

private:
	const CollisionVolumeAABB* beginaabb;
	const CollisionVolumeAABB* endaabb;

	TerrainObject* m_terrain;
	float terrainLength;

	int m_startRow;
	int m_endRow;
	int m_startCol;
	int m_endCol;

	int colLength;
	int activeCol;
	int activeRow;
};

#endif _terrainrectanglearea
#pragma once
