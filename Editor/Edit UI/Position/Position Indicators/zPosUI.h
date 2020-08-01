#ifndef _zposui
#define _zposui
#include "WorldUI.h"

class PositionUI;

//This controls the behavior for the Z position indicator for a selected object
class zPosUI : public WorldUI
{
public:
	zPosUI() = delete;
	zPosUI(const zPosUI&) = delete;
	zPosUI operator=(const zPosUI&) = delete;
	~zPosUI();

	zPosUI(PositionUI*);

	//This is the behavior for forward movement for this indicator
	void ForwardMovement(Serializable*) override;

	//This is the behavior for backward movement for this indicator
	void BackwardMovement(Serializable*) override;

	//This displays the Z indicator
	void Display(float radius, const Vect& center) override;

	//This is a callback when this indicator is selected
	void Selected() override;

private:
	PositionUI* posUIcoll;
};

#endif _zposui
#pragma once
