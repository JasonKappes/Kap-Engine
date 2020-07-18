#ifndef _xrotui
#define _xrotui
#include "WorldUI.h"

class RotationUI;

class xRotUI : public WorldUI
{
public:
	xRotUI() = delete;
	xRotUI(const xRotUI&) = delete;
	xRotUI operator=(const xRotUI&) = delete;
	~xRotUI();

	xRotUI(RotationUI*);

	void Display(float radius, const Vect& center) override;

	void Selected() override;

	void LeftMovement(Serializable*) override;

	void RightMovement(Serializable*) override;

	void ForwardMovement(Serializable*) override;

	void BackwardMovement(Serializable*) override;


private:
	RotationUI* rotUIcoll;
	float modelRadius;
	float rotationSlowFactor;
};

#endif _xrotui
#pragma once
