#ifndef _aabbrender
#define _aabbrender
#include "VolumeShow.h"
#include "VisualizerAttorney.h"

class AABBRender : public VolumeShow
{
public:
	AABBRender() = default;
	AABBRender(const AABBRender&) = delete;
	AABBRender operator=(const AABBRender&) = delete;
	~AABBRender() = default;

	const void ShowCollisionVolume(Matrix& t_world, const Vect& t_color) const override
	{
		VisualizerAttorney::Box::RenderAABB(t_world, t_color);
	}
};

#endif _aabbrender
#pragma once
