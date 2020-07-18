#ifndef _selectionvolume
#define _selectionvolume
#include "Matrix.h"

class Touchable;
class Transform;
class Selectable;

class SelectionVolume
{
public:
	SelectionVolume() : objtransform(nullptr) {}
	SelectionVolume(const SelectionVolume&) = delete;
	virtual ~SelectionVolume() = default;

	virtual bool MouseSelectionIntersection() = 0;

	const Transform& GetTransform() { return *objtransform;  }

	const Transform* objtransform;
};

#endif _selectionvolume
#pragma once
