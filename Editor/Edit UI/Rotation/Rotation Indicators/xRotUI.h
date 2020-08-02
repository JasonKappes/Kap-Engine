#ifndef _xrotui
#define _xrotui
#include "WorldUI.h"

class RotationUI;

//Responsible for the behavior of the X rotation UI indicator
class xRotUI : public WorldUI
{
public:
	xRotUI() = delete;
	xRotUI(const xRotUI&) = delete;
	xRotUI operator=(const xRotUI&) = delete;
	~xRotUI();

	xRotUI(RotationUI*);

	//Renders the ring around a given position with a given radius
	void Display(float radius, const Vect& center) override;

	//Callback for when this object is selected
	void Selected() override;

	//This defines the behavior (if selected) upon left movement of the mouse
	void LeftMovement(Serializable*) override;

	//This defines the behavior (if selected) upon right movement of the mouse	
	void RightMovement(Serializable*) override;

	//This defines the behavior (if selected) upon forward movement of the mouse
	void ForwardMovement(Serializable*) override;

	//This defines the behavior (if selected) upon backward movement of the mouse
	void BackwardMovement(Serializable*) override;

private:
	RotationUI* rotUIcoll;
	float modelRadius;
	float rotationSlowFactor;
};

#endif _xrotui
#pragma once
