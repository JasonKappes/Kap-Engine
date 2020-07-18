#ifndef _groupUI
#define _groupUI
#include "Matrix.h"
#include "EmptyIndicator.h"

class WorldUI;

class GroupUI
{
public:
	GroupUI();
	GroupUI(const GroupUI&) = delete;
	virtual ~GroupUI();

	virtual void UpdateUI(float radius, const Vect& center) = 0;

	virtual void DrawUI() = 0;

	virtual void ResetIndicator() {}

	virtual void EnableIndicator() {}

	virtual void ForwardAdjustment() {}

	virtual void LeftAdjustment() {}

	virtual void RightAdjustment() {}

	virtual void BackwardAdjustment() {}

	virtual void SetIndicator(WorldUI* t_selectedIndicator);

	void EmptyIndicatorSelected();

	WorldUI& GetSelectedIndicator();

protected:
	WorldUI* selectedIndicator;
	EmptyIndicator* emptyIndicator;
};

#endif _groupUI
#pragma once
