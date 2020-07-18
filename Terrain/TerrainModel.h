
#ifndef _TerrainModel
#define _TerrainModel

#include <tuple>
#include <d3d11.h>
#include "Matrix.h"
#include "Model.h"
#include "GpuVertTypes.h"
#include "GameObject.h"

class Model;
struct ID3D11DeviceContext;
struct ID3D11Device;
class GraphicsObject_TextureFlat;
class GraphicsObject_TextureLight;
class GraphicsObject_ColorNoTextureLight;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class PlayerTank;
class CollisionVolume;
class Transform;

class TerrainModel
{
public:
	TerrainModel() = delete;
	TerrainModel(const TerrainModel&) = delete;					// Copy constructor
	TerrainModel(Model&&) = delete;								// Move constructor
	TerrainModel& operator=(const TerrainModel&) & = delete;	// Copy assignment operator
	TerrainModel& operator=(TerrainModel&&) & = delete;			// Move assignment operator
	TerrainModel(Transform*, const char* file, const char* texture, float len, float maxheight, float ytrans, int RepeatU, int RepeatV);
	~TerrainModel();

	const VertexStride_VUN& GetVerts() const;
	float GetLength() const;

	float GetMaxHeight() const;

private:
	int TexelIndex(int, int, int);
	int vertexIndex(float, int, int);

private:
	VertexStride_VUN* pVerts;
	GraphicsObject_TextureFlat* GOflat;
	GLbyte* imgData;
	Model* pModTerrain;
	Vect* pVect;

	float originPointX;
	float originPointZ;
	float cellWidth;
	float cellScale;

	float maxHeight;
	int imgHeight;
	int pixel_width;

	int vind = 0;
	float length;
};

#endif _TerrainModel