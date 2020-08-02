#ifndef _obbrender
#define _obbrender
#include "VolumeShow.h"
#include "VisualizerAttorney.h"

//Renders an OBB (oriented bounding box) at the given world location, with the given color
class OBBRender : public VolumeShow
{
public:
	OBBRender() = default;
	OBBRender(const OBBRender&) = delete;
	OBBRender operator=(const OBBRender&) = delete;
	~OBBRender() = default;

	const void ShowCollisionVolume(Matrix& t_world, const Vect& t_color) const override
	{
		VisualizerAttorney::Box::RenderOBB(t_world, t_color);
	}
};

#endif _obbrender
#pragma once
