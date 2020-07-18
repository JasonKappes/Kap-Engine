#ifndef _positionui
#define _positionui
#include "GroupUI.h"

class xPosUI;
class yPosUI;
class zPosUI;
class WorldUI;
class EmptyUI;

class PositionUI : public GroupUI
{
public:
	PositionUI();
	PositionUI(const PositionUI&) = delete;
	PositionUI operator=(const PositionUI&) = delete;
	~PositionUI();

	void EnableIndicator() override;

	void ResetIndicator() override;

	void UpdateUI(float radius, const Vect& center) override;

	void DrawUI() override;

private:
	xPosUI* xindicator;
	zPosUI* zindicator;
	yPosUI* yindicator;
};

#endif _positionui
#pragma once
