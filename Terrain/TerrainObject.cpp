#include "TerrainObject.h"
#include "TerrainModel.h"
#include "CollisionVolumeAABB.h"
#include "VisualizerAttorney.h"
#include "KapMathTools.h"
#include "TerrainRectangleArea.h"
#include "Color.h"
#define NOT_IN_TERRAIN -100000.f;

TerrainObject::~TerrainObject() 
{ 
	delete this->terrainModel; 
	delete this->terrainAABB;
	delete this->endAABB;
}

TerrainObject::TerrainObject(const char* file, const char* texture, float len, float maxheight, float ytrans, int RepeatU, int RepeatV)
{
	this->terrainModel = new TerrainModel(this->transform, file, texture, len, maxheight, ytrans, RepeatU, RepeatV);

	terrainAABB = new CollisionVolumeAABB();
	endAABB = new CollisionVolumeAABB();

	//transform->position = Vect(-64247.0f, -2600.0f, -337488.0f);
	transform->rotation = Matrix(IDENTITY);
	transform->scale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	transform->UpdateWorld();

}

void TerrainObject::SceneEntry()
{
	Drawable::SubmitDrawRegistration();
}

void TerrainObject::SceneExit()
{
	Drawable::SubmitDrawDeRegistration();
}

void TerrainObject::Draw()
{
	transform->Render();
}

void TerrainObject::GetRowCol(int& row, int& col, const Vect& objPos)
{
	//calculate center collision point
	float originpointx = transform->position.X();

	float originpointz = transform->position.Z();

	int celloffsetX = (int)((originpointx + terrainModel->GetLength()) - objPos.X());

	int celloffsetZ = (int)(objPos.Z() - originpointz);

	row = (int)(celloffsetX);

	col = (int)(celloffsetZ);
}

TerrainRectangleArea* TerrainObject::GetCollisionArea(const Vect& pos, float radius)
{
	int collisionWidth = (int)(radius / 1.0f); //add one to round up

	int row, col;

	GetRowCol(row, col, pos);

	int endRow		= MININT;
	int startRow	= MAXINT;

	//get start and end row
	for (int neighboringRow = -collisionWidth; neighboringRow <= collisionWidth; ++neighboringRow)
	{
		if ((row + neighboringRow >= 0) && (row + neighboringRow < (terrainModel->GetLength() - 2)))
		{
			endRow = row + neighboringRow; //always setting latest end row

			if (endRow < startRow) startRow = endRow; 
		}
	}

	int endCol		= MININT;
	int startCol	= MAXINT;

	//get start and end col
	for (int neighboringCol = -collisionWidth; neighboringCol <= collisionWidth; ++neighboringCol)
	{
		if (((col + neighboringCol) >= 0) && (col + neighboringCol < (terrainModel->GetLength() - 1)))
		{
			endCol = col + neighboringCol; //always setting latest end col

			if (endCol < startCol) startCol = endCol;
		}
	}

	return new TerrainRectangleArea(this, this->terrainModel->GetLength(), startRow, endRow, startCol, endCol);

}

const CollisionVolumeAABB& TerrainObject::privGetCellVolume(CollisionVolumeAABB* vol, float len, int row, int col)
{
	const VertexStride_VUN* pVerts = &this->terrainModel->GetVerts();

	Vect topleft = Vect(pVerts[vertexIndex(len, row, col)].x, pVerts[vertexIndex(len, row, col)].y, pVerts[vertexIndex(len, row, col)].z);
	Vect bottomleft = Vect(pVerts[vertexIndex(len, row + 1, col)].x, pVerts[vertexIndex(len, row + 1, col)].y, pVerts[vertexIndex(len, row + 1, col)].z);
	Vect topright = Vect(pVerts[vertexIndex(len, row, col + 1)].x, pVerts[vertexIndex(len, row, col + 1)].y, pVerts[vertexIndex(len, row, col + 1)].z);
	Vect bottomright = Vect(pVerts[vertexIndex(len, row + 1, col + 1)].x, pVerts[vertexIndex(len, row + 1, col + 1)].y, pVerts[vertexIndex(len, row + 1, col + 1)].z);

	Vect min = topleft;
	Vect max = topleft;

	CalculateMinMax(min, max, bottomleft);
	CalculateMinMax(min, max, topright);
	CalculateMinMax(min, max, bottomright);

	Vect aabbmin = min * transform->GetWorld();
	Vect aabbmax = max * transform->GetWorld();

	Vect pos = Vect((float)row, 0.0f, (float)col);

	vol->SetMin(aabbmin);
	vol->SetMax(aabbmax);
	vol->MinMaxOBBData();


	return *vol;
}

bool TerrainObject::ValidCell(int row, int col)
{
	return (row >= 0 && row < this->terrainModel->GetLength()) && (col >= 0 && col < this->terrainModel->GetLength());
}

const CollisionVolumeAABB& TerrainObject::GetCellVolume(float len, int row, int col)
{
	return privGetCellVolume(terrainAABB, len, row, col);
}

const CollisionVolumeAABB& TerrainObject::GetEndVolume(float len, int endrow, int endcol)
{
	return privGetCellVolume(endAABB, len, endrow, endcol);
}

int TerrainObject::vertexIndex(float len, int row, int col)
{
	return (int)(row * len) + col;
}

void TerrainObject::CalculateMinMax(Vect& min, Vect& max, Vect& tmp)
{
	if (tmp.X() > max.X()) max.X() = tmp.X();
	else if (tmp.X() < min.X()) min.X() = tmp.X();

	if (tmp.Y() > max.Y()) max.Y() = tmp.Y();
	else if (tmp.Y() < min.Y()) min.Y() = tmp.Y();

	if (tmp.Z() > max.Z()) max.Z() = tmp.Z();
	else if (tmp.Z() < min.Z()) min.Z() = tmp.Z();
}

bool TerrainObject::ObjectWithinTerrain(const Vect& pos, int collWidth)
{
	float terrainSize = terrainModel->GetLength() - 1;
	int edge = 1;
	return (((pos.X() + collWidth >= ((int)transform->position.X() + edge)) || pos.X() - collWidth >= ((int)transform->position.X() + edge)))
		&& (((pos.X() + collWidth) < ((int)transform->position.X() + terrainSize)) || ((pos.X() - collWidth) < ((int)transform->position.X() + terrainSize)))
		&& ((pos.Z() + collWidth >= ((int)transform->position.Z() + edge)) || (pos.Z() - collWidth >= ((int)transform->position.Z() + edge)))
		&& ((pos.Z() + collWidth < ((int)transform->position.Z() + (terrainSize))) || (pos.Z() - collWidth < ((int)transform->position.Z() + (terrainSize))))
		&& ((pos.Y() + collWidth >= ((int)transform->position.Y())) || pos.Y() - collWidth <= ((int)transform->position.Y() + this->terrainModel->GetMaxHeight()));
}

bool TerrainObject::PointAboveTerrain(const Vect& pos)
{
	float terrainSize = terrainModel->GetLength() - 1;
	int edge = 1;
	return (((pos.X() >= ((int)transform->position.X() + edge)) && pos.X() >= ((int)transform->position.X() + edge)))
		&& ((pos.X() < ((int)transform->position.X() + terrainSize)) && (pos.X() < ((int)transform->position.X() + terrainSize)))
		&& ((pos.Z() >= ((int)transform->position.Z() + edge)) && (pos.Z() >= ((int)transform->position.Z() + edge)))
		&& ((pos.Z() < ((int)transform->position.Z() + (terrainSize))) && (pos.Z() < ((int)transform->position.Z() + (terrainSize))));
}

float TerrainObject::GetHeightAboveTerrain(const Vect& pos)
{
	if (PointAboveTerrain(pos))
	{
		int row, col;
		GetRowCol(row, col, pos);
		const VertexStride_VUN* pVerts = &this->terrainModel->GetVerts();
		float heightaboveterrain = pos.Y() - pVerts[vertexIndex(terrainModel->GetLength(), row, col)].y;
		return heightaboveterrain;
	}
	else {
		//not a valid position above the terrain, return sub-zero number
		return NOT_IN_TERRAIN;
	}
}

void TerrainObject::ProjectPointOntoTerrain(const Vect& pos)
{
	if (PointAboveTerrain(pos))
	{
		int row, col;
		GetRowCol(row, col, pos);
		privGetCellVolume(this->terrainAABB, this->terrainModel->GetLength(), row, col).DebugView(Color::Red);
	}
}