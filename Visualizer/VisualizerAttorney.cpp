#include "VisualizerAttorney.h"
#include "Visualizer.h"

void VisualizerAttorney::Sphere::ShowBSphere(const CollisionVolumeBSphere& S, const Vect& col)
{
	Visualizer::ShowBSphere(S, col);
}

void VisualizerAttorney::Sphere::ShowBSphere(Vect center, float radius, const Vect& color)
{
	Visualizer::ShowBSphere(center, radius, color);
}

void VisualizerAttorney::Sphere::RenderBSphere(Matrix& S, const Vect& col)
{
	Visualizer::RenderBSphere(S, col);
}

void VisualizerAttorney::Box::ShowAABB(const CollisionVolumeAABB& aabb, const Vect& color)
{
	Visualizer::ShowAABB(aabb, color);
}

void VisualizerAttorney::Box::RenderAABB(Matrix& world, const Vect& color)
{
	Visualizer::RenderAABB(world, color);
}

void VisualizerAttorney::Box::ShowOBB(const CollisionVolumeOBB& obb, const Vect& color)
{
	Visualizer::ShowOBB(obb, color);
}

void VisualizerAttorney::Box::RenderOBB(Matrix& world, const Vect& color)
{
	Visualizer::RenderOBB(world, color);
}

void VisualizerAttorney::GameLoop::VisualizeAll()
{
	Visualizer::VisualizeAll();
}

void VisualizerAttorney::GameLoop::Delete()
{
	Visualizer::Delete();
}
