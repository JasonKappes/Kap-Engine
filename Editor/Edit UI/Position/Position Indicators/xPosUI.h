#ifndef _xposui
#define _xposui
#include "WorldUI.h"

class PositionUI;

//This class controls the behavior for the X Position Indicator for a selected object
class xPosUI : public WorldUI
{
public: // ENGINE METHODS
	xPosUI() = delete;
	xPosUI(const xPosUI&) = delete;
	xPosUI operator=(const xPosUI&) = delete;
	~xPosUI();

	xPosUI(PositionUI*);
	
	//Displays the position indicator
	void Display(float radius, const Vect& center) override;
	
	//A callback if this indicator is selected
	void Selected() override;

	//The behavior if the indicator is moved left
	void LeftMovement(Serializable*) override;

	//The behavior if the indicator is moved right
	void RightMovement(Serializable*) override;

private:
	PositionUI* posUIcoll;
};

#endif _xposui
#pragma once
