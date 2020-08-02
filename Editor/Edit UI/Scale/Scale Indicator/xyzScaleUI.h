#ifndef _xyzscaleui
#define _xyzscaleui
#include "WorldUI.h"

class ScaleUI;

//This controls the behavior for the xyzscale indicator
class xyzScaleUI : public WorldUI
{
public:
	xyzScaleUI() = delete;
	xyzScaleUI(const xyzScaleUI&) = delete;
	xyzScaleUI operator=(const xyzScaleUI&) = delete;
	~xyzScaleUI();

	xyzScaleUI(ScaleUI*);

	//This displays the updates the world information for this indicator
	void Display(float radius, const Vect& center) override;

	//This is a callback when this object is selected
	void Selected() override;

	//This defines the behavior for this object (if selected) when the mouse is moved left
	void LeftMovement(Serializable*) override;

	//This defines the behavior for this object (if selected) when the mouse is moved right
	void RightMovement(Serializable*) override;

private:
	ScaleUI* scaleUIcoll;
	float modelRadius;
	float scaleRate;
};

#endif _yrotui
#pragma once
