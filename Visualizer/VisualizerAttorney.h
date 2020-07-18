#ifndef _visualizerattorney
#define _visualizerattorney

class Vect;
class Matrix;
class CollisionVolumeAABB;
class CollisionVolumeOBB;
class CollisionVolumeBSphere;

class VisualizerAttorney
{
public:

	class Sphere
	{
		friend class CollisionVolumeBSphere;
		friend class BSphereRender;
		friend class ActiveObject;
		friend class CollisionVolumeAABB;
		friend class CollisionVolumeOBB;
	private:
		static void ShowBSphere(const CollisionVolumeBSphere& S, const Vect& color);
		static void ShowBSphere(Vect center, float radius, const Vect& color);
		static void RenderBSphere(Matrix& S, const Vect& color);

	private:
		Sphere() = delete;
		Sphere(const Sphere&) = delete;
		Sphere operator=(const Sphere&) = delete;
		~Sphere() = delete;
	};

	class Box
	{
		friend class CollisionVolumeAABB;
		friend class CollisionVolumeOBB;
		friend class AABBRender;
		friend class OBBRender;
		friend class CollidableGroup;
		friend class CollisionTestTerrainCommand;
		friend class xRotUI;
		friend class yRotUI;
		friend class zRotUI;
	private:
		static void ShowAABB(const CollisionVolumeAABB&, const Vect& color);
		static void RenderAABB(Matrix& S, const Vect& color);
		static void ShowOBB(const CollisionVolumeOBB&, const Vect& color);
		static void RenderOBB(Matrix& S, const Vect& color);
	};

	class GameLoop
	{
		friend class KapEngine;
	private:
		static void VisualizeAll();
		static void Delete();

	private:
		GameLoop() = delete;
		GameLoop(const GameLoop&) = delete;
		GameLoop operator=(const GameLoop&) = delete;
		~GameLoop() = default;
	};

private:
	VisualizerAttorney() = delete;
	VisualizerAttorney(const VisualizerAttorney&) = delete;
	VisualizerAttorney operator=(const VisualizerAttorney&) = delete;
	~VisualizerAttorney() = delete;
};

#endif _visualizerattorney
#pragma once
