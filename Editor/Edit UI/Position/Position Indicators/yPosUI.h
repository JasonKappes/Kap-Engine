#ifndef _yposui
#define _yposui
#include "WorldUI.h"

class PositionUI;

class yPosUI : public WorldUI
{
public:
	yPosUI() = delete;
	yPosUI(const yPosUI&) = delete;
	yPosUI operator=(const yPosUI&) = delete;
	~yPosUI();

	yPosUI(PositionUI*);

	void ForwardMovement(Serializable*) override;

	void BackwardMovement(Serializable*) override;

	void Display(float radius, const Vect& center) override;

	void Selected() override;

private:
	PositionUI* posUIcoll;
};

#endif _yposui
#pragma once
