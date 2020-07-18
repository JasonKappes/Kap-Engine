#ifndef _yrotui
#define _yrotui
#include "WorldUI.h"

class RotationUI;

class yRotUI : public WorldUI
{
public:
	yRotUI() = delete;
	yRotUI(const yRotUI&) = delete;
	yRotUI operator=(const yRotUI&) = delete;
	~yRotUI();

	yRotUI(RotationUI*);

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
