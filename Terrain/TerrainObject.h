#ifndef _terrainobject
#define _terrainobject
#include "GameObject.h"
#include "Matrix.h"

class TerrainModel;
class CollisionVolumeAABB;
class TerrainRectangleArea;
class Transform;

class TerrainObject : public GameObject //Making it a gameobject to have access to transform
{
public:
	TerrainObject() = delete;
	TerrainObject(const TerrainObject&) = delete;
	TerrainObject operator=(const TerrainObject&) = delete;
	~TerrainObject();

	TerrainObject(const char* file, const char* texture, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);

	void SceneEntry() override;

	void SceneExit() override;

	void Draw() override;

	void Update() override {}

	float GetHeightAboveTerrain(const Vect& pos);

	void ProjectPointOntoTerrain(const Vect& pos);
	
	bool ObjectWithinTerrain(const Vect& pos, int radius);

	TerrainRectangleArea* GetCollisionArea(const Vect& pos, float radius);

	const CollisionVolumeAABB& GetCellVolume(float len, int row, int col);

	const CollisionVolumeAABB& GetEndVolume(float len, int endrow, int endcol);

private:
	const CollisionVolumeAABB& privGetCellVolume(CollisionVolumeAABB*, float len, int row, int col);
	bool ValidCell(int row, int col);
	int vertexIndex(float len, int i, int j);
	void CalculateMinMax(Vect& min, Vect& max, Vect& v);
	void GetRowCol(int& row, int& col, const Vect& objPos);

	bool PointAboveTerrain(const Vect& pos);


private:
	TerrainModel* terrainModel;

	CollisionVolumeAABB* terrainAABB;
	CollisionVolumeAABB* endAABB;
};

#endif _terrainobject
#pragma once
