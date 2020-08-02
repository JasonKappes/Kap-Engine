#ifndef _selectedobject
#define _selctedobject
#include "Matrix.h"
#include "Serializable.h"
#include "EmptyUI.h"

class Serializable;
class Adjustment;

//Strategy pattern base class for Active Object vs. Empty Object
class SelectedObject
{
public:
	SelectedObject(); 
	SelectedObject(const SelectedObject&) = delete;
	virtual ~SelectedObject();

public:
	enum class adjustment { position, rotation, scale, none };

public:
	virtual void ForwardAdjustment() {}
	virtual void RightAdjustment() {}
	virtual void LeftAdjustment() {}
	virtual void BackwardAdjustment() {}

	virtual void SetAdjustmentType(adjustment) {}

	virtual void ShowSelection() = 0;

	virtual void DrawUI() {}

	virtual void SetObjectForAdjustment(Serializable*);

	virtual void SnapToObject() {}

	virtual void Duplicate() {}

	virtual void Erase() {}

	void DisableIndicators()	{ active_ui->ResetIndicator();	}

	void SetEmptyUI()			{ active_ui = empty_ui;			}

	void SetEmptyIndicator()	{ active_ui->EmptyIndicatorSelected();			}

protected:
	GroupUI* active_ui;
	EmptyUI* empty_ui;
	Serializable* selectedObject;
};

#endif _selectedobject
#pragma once
