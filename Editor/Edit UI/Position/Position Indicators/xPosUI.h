#ifndef _xposui
#define _xposui
#include "WorldUI.h"

class PositionUI;

class xPosUI : public WorldUI
{
public:
	xPosUI() = delete;
	xPosUI(const xPosUI&) = delete;
	xPosUI operator=(const xPosUI&) = delete;
	~xPosUI();

	xPosUI(PositionUI*);

	void Display(float radius, const Vect& center) override;

	void Selected() override;

	void LeftMovement(Serializable*) override;

	void RightMovement(Serializable*) override;


private:
	PositionUI* posUIcoll;
};

#endif _xposui
#pragma once
