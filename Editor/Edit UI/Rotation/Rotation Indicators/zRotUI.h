#ifndef _zrotui
#define _zrotui
#include "WorldUI.h"

class RotationUI;

//This defines the behavior for the Z rotation indicator
class zRotUI : public WorldUI
{
public:
	zRotUI() = delete;
	zRotUI(const zRotUI&) = delete;
	zRotUI operator=(const zRotUI&) = delete;
	~zRotUI();

	zRotUI(RotationUI*);

	//This renders this indicator at a given position with radius
	void Display(float radius, const Vect& center) override;

	//This is a callback when this object is selected
	void Selected() override;

	//This defines the behavior for this object (when selected) if the mouse is moved left
	void LeftMovement(Serializable*) override;

	//This defines the behavior for this object (when selected) if the mouse is moved right
	void RightMovement(Serializable*) override;

	//This defines the behavior for this object (when selected) if the mouse is moved forward
	void ForwardMovement(Serializable*) override;

	//This defines the behavior for this object (when selected) if the mouse is moved backward
	void BackwardMovement(Serializable*) override;


private:
	RotationUI* rotUIcoll;
	float modelRadius;
	float rotationSlowFactor;
};

#endif _yrotui
#pragma once
