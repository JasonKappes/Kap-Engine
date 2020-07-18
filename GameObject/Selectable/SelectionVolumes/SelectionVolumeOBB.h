#ifndef _selectionvolumeobb
#define _selectionvolumeobb
#include "SelectionVolume.h"

class Transform;

class SelectionVolumeOBB : public SelectionVolume
{
public:
	SelectionVolumeOBB() = delete;
	SelectionVolumeOBB(const Transform*);
	SelectionVolumeOBB(const SelectionVolumeOBB&) = delete;
	SelectionVolumeOBB operator=(const SelectionVolumeOBB&) = delete;
	~SelectionVolumeOBB() = default;

	bool MouseSelectionIntersection() override;

private:
	void CalculateMinMax();

private:
	Vect min;
	Vect max;

};

#endif _selectionvolumeobb
#pragma once