#ifndef _zrotui
#define _zrotui
#include "WorldUI.h"

class RotationUI;

class zRotUI : public WorldUI
{
public:
	zRotUI() = delete;
	zRotUI(const zRotUI&) = delete;
	zRotUI operator=(const zRotUI&) = delete;
	~zRotUI();

	zRotUI(RotationUI*);

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

#endif _yrotui
#pragma once
