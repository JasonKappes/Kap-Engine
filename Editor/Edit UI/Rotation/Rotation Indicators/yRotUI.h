#ifndef _yrotui
#define _yrotui
#include "WorldUI.h"

class RotationUI;

//This defines the behavior for the Y rotation indicator
class yRotUI : public WorldUI
{
public:
	yRotUI() = delete;
	yRotUI(const yRotUI&) = delete;
	yRotUI operator=(const yRotUI&) = delete;
	~yRotUI();

	yRotUI(RotationUI*);

	//This displays this indicator when 
	void Display(float radius, const Vect& center) override;

	//This is a callback when this object is selected
	void Selected() override;

	//This defines the behavior for this object (if selected) when the mouse is moved left.
	void LeftMovement(Serializable*) override;

	//This defines the behavior for this object (if selected) when the mouse is moved right.
	void RightMovement(Serializable*) override;

	//This defines the behavior for this object (if selected) when the mouse is moved forward.
	void ForwardMovement(Serializable*) override;

	//This defines the behavior for this object (if selected) when the mouse is moved down.
	void BackwardMovement(Serializable*) override;


private:
	RotationUI* rotUIcoll;
	float modelRadius;
	float rotationSlowFactor;
};

#endif _yrotui
#pragma once
