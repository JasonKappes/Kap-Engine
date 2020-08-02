#ifndef _emptyobject
#define _emptyobject
#include "SelectedObject.h"

//This is the "selected object" when no object is selected (in world edit mode)
class EmptyObject : public SelectedObject
{
public:
	EmptyObject() = default;
	EmptyObject(const EmptyObject&) = delete;
	~EmptyObject() = default;

	virtual void ShowSelection() override { } //do nothing
};

#endif _emptyobject
#pragma once
