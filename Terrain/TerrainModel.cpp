#include "TerrainModel.h"
#include <assert.h>
#include "Color.h"
#include "sb6.h"
#include <TextureTGA.h>
#include <DebugOut.h>
#include "GraphicsObject_TextureFlat.h"
#include "GraphicsObject_TextureLight.h"
#include "GraphicsObject_ColorNoTextureLight.h"
#include "ShaderManager.h"
#include "TextureManager.h"

TerrainModel::TerrainModel(Transform* object_transform, const char* file, const char* texture, float t_len, float maxheight, float , int RepeatU, int RepeatV)
{
	int imgWidth = 0, icomp = 0;
	unsigned int dtype = 0;
	imgData = gltReadTGABits(file, &imgWidth, &imgHeight, &icomp, &dtype);
	assert(imgWidth == imgHeight && imgWidth != 0); // We need square images for heightmaps
	this->length = t_len;

	imgHeight;	// the image should be square
	pixel_width = 3;			// 3 bytes RGB per pixel

	this->maxHeight = maxheight;

	int nverts = (int)(length * length);
	pVerts = new VertexStride_VUN[nverts];

	float ntri = ((float)length - 1) * ((float)length - 1) * 2;
	TriangleIndex* pTriList = new TriangleIndex[(unsigned int)ntri];

	float y_val = 0;
	int y = 0, z = 0, ind = 0;

	cellScale = length / (float)imgHeight;

	cellWidth = imgHeight * cellScale;


	//Calculate vertex world and height data
	for (int row = ((int)length - 1); row >= 0; row--)
	{
		for (int col = 0; col < length; col++)
		{
			y = (int)((float)row / cellScale);
			z = (int)((float)col / cellScale);

			y_val = static_cast<unsigned char>(imgData[pixel_width * TexelIndex(imgHeight, y, z)]) / ((float)(255 / maxheight));

			ind = vertexIndex(length, row, col);

			float xcord = length - (float)row;

			pVerts[ind].set(xcord, (float)y_val, (float)col,
				(float)(row * (RepeatU / (length - 1))), (float)(col * (RepeatV / (length - 1))), 0.0f, 0.0f, 0.0f, 0.0f);

		}
	}

	//winding, calculate normals
	for (int row = 0, tind = 0; row < length - 2; row++)
	{
		for (int col = 0; col < length - 1; col++)
		{
			pTriList[tind++].set((int)(col + (length * row) + 1), (int)(col + (length * row)), (int)(col + length + (length * row)));
			pTriList[tind++].set((int)(col + (length * row) + 1), (int)(col + length + (length * row)), (int)(col + length + (length * row) + 1));

			if (row != 0 && col != 0 && row != length - 2 && col != length - 2)
			{
				//CalculateNormals(length, row, col);
			}
		}
	}

	pModTerrain = new Model(pVerts, nverts, pTriList, (int)ntri);

	this->GOflat = new GraphicsObject_TextureFlat(pModTerrain, ShaderManager::Get("textureFlatRender"), TextureManager::Get(texture));

	object_transform->SetGraphicsObject(this->GOflat);
	object_transform->scale = Matrix(SCALE, 1.0f, 1.0f, 1.0f);
	object_transform->rotation = Matrix(IDENTITY);
	object_transform->UpdateWorld();

	delete[] pTriList;
}

int TerrainModel::vertexIndex(float len, int row, int col)
{
	return (int)(row * len) + col;
}

float TerrainModel::GetMaxHeight() const
{
	return this->maxHeight;
}

int TerrainModel::TexelIndex(int side, int row, int col)
{
	return col * side + row;
}

TerrainModel::~TerrainModel() 
{ 
	delete[] pVerts;
	delete this->pModTerrain; 
}

const VertexStride_VUN& TerrainModel::GetVerts() const
{
	return *pVerts;
}

float TerrainModel::GetLength() const
{
	return this->length;
}
