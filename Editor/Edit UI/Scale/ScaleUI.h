#ifndef _scaleui
#define _scaleui
#include "GroupUI.h"

class xyzScaleUI;

class ScaleUI : public GroupUI
{
public:
	ScaleUI();
	ScaleUI(const ScaleUI&) = delete;
	ScaleUI operator=(const ScaleUI&) = delete;
	~ScaleUI();

	void EnableIndicator() override;

	void ResetIndicator() override;

	void UpdateUI(float radius, const Vect& center) override;

	void DrawUI() override;

private:
	xyzScaleUI* scaleIndicator;
	float modelRadius;
};

#endif _scaleui
#pragma once
