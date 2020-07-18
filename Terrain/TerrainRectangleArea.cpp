#include "TerrainRectangleArea.h"
#include "TerrainObject.h"
#include "TRAIterator.h"
#include "CollisionVolumeAABB.h"

TerrainRectangleArea::TerrainRectangleArea(TerrainObject* terrain, float t_terrainlength, int startRow, int endRow, int startCol, int endCol)
{
	this->m_terrain = terrain;
	this->terrainLength = t_terrainlength;

	this->m_startRow = startRow;
	this->m_endRow = endRow;
	this->m_startCol = startCol;
	this->m_endCol = endCol;

	this->colLength = m_endCol - m_startCol;
	this->activeCol = -1;
	this->activeRow = -1;
}

const CollisionVolumeAABB& TerrainRectangleArea::GetNextCell()
{
	++this->activeCol;

	this->activeCol = this->activeCol % (this->colLength + 1);

	if (this->activeCol == 0) ++activeRow;

	return m_terrain->GetCellVolume(terrainLength, activeRow + m_startRow, activeCol + m_startCol);
}

const CollisionVolumeAABB& TerrainRectangleArea::begin()
{
	return m_terrain->GetCellVolume(terrainLength, m_startRow, m_startCol);
}

const CollisionVolumeAABB& TerrainRectangleArea::end()
{
	return m_terrain->GetEndVolume(terrainLength, m_endRow, m_endCol);
}
