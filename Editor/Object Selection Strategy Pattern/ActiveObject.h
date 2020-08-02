#ifndef _activeobject
#define _activeobject
#include "SelectedObject.h"

class Serializable;
class PositionUI;
class RotationUI;
class EmptyUI;
class ScaleUI;
class GroupUI;

//This manages the overall behavior for selected objects
class ActiveObject : public SelectedObject
{
public:
	ActiveObject();
	ActiveObject(const ActiveObject&) = delete;
	ActiveObject operator=(const ActiveObject&) = delete;
	~ActiveObject();

	//Calls the forward movement behavior of the current indicator
	virtual void ForwardAdjustment() override;
	
	//Calls the right movement behavior of the current indicator
	virtual void RightAdjustment() override;
	
	//Calls the left movement behavior of the current indicator
	virtual void LeftAdjustment()  override;
	
	//Calls the backward movement behavior of the current indicator
	virtual void BackwardAdjustment()  override;
	
	//Sends world information for the selected object to the selected indicators
	virtual void ShowSelection() override;
	
	//Selects the current indicator group (pos/scale/rot) based on adjustment type
	virtual void SetAdjustmentType(SelectedObject::adjustment) override;
	
	//Switches to a topdown view of the selected object
	virtual void SnapToObject() override;
	
	//Duplicates the selected object (duplicate object can be selected, moved, and is saved)
	virtual void Duplicate() override;
	
	//Deletes this object (won't display during any future runs)
	virtual void Erase() override;
	
	//Calls the indicator group to render its indicators
	virtual void DrawUI() override;

private:
	PositionUI* position_ui;
	RotationUI* rotation_ui;
	ScaleUI* scale_ui;

};

#endif _activeobject
#pragma once
