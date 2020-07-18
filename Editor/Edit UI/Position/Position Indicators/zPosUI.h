#ifndef _zposui
#define _zposui
#include "WorldUI.h"

class PositionUI;

class zPosUI : public WorldUI
{
public:
	zPosUI() = delete;
	zPosUI(const zPosUI&) = delete;
	zPosUI operator=(const zPosUI&) = delete;
	~zPosUI();

	zPosUI(PositionUI*);

	void ForwardMovement(Serializable*) override;

	void BackwardMovement(Serializable*) override;

	void Display(float radius, const Vect& center) override;

	void Selected() override;

private:
	PositionUI* posUIcoll;
};

#endif _zposui
#pragma once
