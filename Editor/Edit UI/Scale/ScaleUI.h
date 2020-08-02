#ifndef _scaleui
#define _scaleui
#include "GroupUI.h"

class xyzScaleUI;

//Manages the scale indicators 
class ScaleUI : public GroupUI
{
public:
	ScaleUI();
	ScaleUI(const ScaleUI&) = delete;
	ScaleUI operator=(const ScaleUI&) = delete;
	~ScaleUI();

	//This allows the various scale indicators to be selected (registers them for selection)
	void EnableIndicator() override;

	//This removes the scale indicators from being selected (deregisters them for selection)
	void ResetIndicator() override;

	//Tells each scale indicator to be rendered
	void UpdateUI(float radius, const Vect& center) override;

	//Updates scale indicators world information
	void DrawUI() override;

private:
	xyzScaleUI* scaleIndicator;
	float modelRadius;
};

#endif _scaleui
#pragma once
