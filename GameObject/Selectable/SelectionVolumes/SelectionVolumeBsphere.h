#ifndef _selectionvolumebsphere
#define _selectionvolumebsphere
#include "SelectionVolume.h"

class Transform;
class Selectable;

class SelectionVolumeBsphere : public SelectionVolume
{
public:
	SelectionVolumeBsphere() = delete;
	SelectionVolumeBsphere(const Transform*);
	SelectionVolumeBsphere(const SelectionVolumeBsphere&) = delete;
	SelectionVolumeBsphere operator=(const SelectionVolumeBsphere&) = delete;
	~SelectionVolumeBsphere() = default;

	bool MouseSelectionIntersection() override;

};

#endif _selectionvolumebsphere
#pragma once