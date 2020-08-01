#ifndef _yposui
#define _yposui
#include "WorldUI.h"

class PositionUI;

//This class controls the behavior for the Y position indicator for a selected object
class yPosUI : public WorldUI
{
public:
	yPosUI() = delete;
	yPosUI(const yPosUI&) = delete;
	yPosUI operator=(const yPosUI&) = delete;
	~yPosUI();

	yPosUI(PositionUI*);

	//This describes the behavior if this indicator is dragged upward
	void ForwardMovement(Serializable*) override;

	//This describes the behavior if this indicator is dragged downward
	void BackwardMovement(Serializable*) override;

	//This displays this indicator, when told too
	void Display(float radius, const Vect& center) override;

	//This is a callback when this indicator is selected
	void Selected() override;

private:
	PositionUI* posUIcoll;
};

#endif _yposui
#pragma once
