#ifndef _xyzscaleui
#define _xyzscaleui
#include "WorldUI.h"

class ScaleUI;

class xyzScaleUI : public WorldUI
{
public:
	xyzScaleUI() = delete;
	xyzScaleUI(const xyzScaleUI&) = delete;
	xyzScaleUI operator=(const xyzScaleUI&) = delete;
	~xyzScaleUI();

	xyzScaleUI(ScaleUI*);

	void Display(float radius, const Vect& center) override;

	void Selected() override;

	void LeftMovement(Serializable*) override;

	void RightMovement(Serializable*) override;

private:
	ScaleUI* scaleUIcoll;
	float modelRadius;
	float scaleRate;
};

#endif _yrotui
#pragma once
