#ifndef _bsphererender
#define _bsphererender
#include "VolumeShow.h"
#include "VisualizerAttorney.h"

class BSphereRender : public VolumeShow
{
public:
	BSphereRender() = default;
	BSphereRender(const BSphereRender&) = delete;
	BSphereRender operator=(const BSphereRender&) = delete;
	~BSphereRender() = default;

	const void ShowCollisionVolume(Matrix& t_world, const Vect& t_color) const override
	{
		VisualizerAttorney::Sphere::RenderBSphere(t_world, t_color);
	}
};

#endif _bsphererender
#pragma once
