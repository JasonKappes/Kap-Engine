#ifndef _activeobject
#define _activeobject
#include "SelectedObject.h"

class Serializable;
class PositionUI;
class RotationUI;
class EmptyUI;
class ScaleUI;
class GroupUI;

class ActiveObject : public SelectedObject
{
public:
	ActiveObject();
	ActiveObject(const ActiveObject&) = delete;
	ActiveObject operator=(const ActiveObject&) = delete;
	~ActiveObject();

	virtual void ForwardAdjustment() override;
	virtual void RightAdjustment() override;
	virtual void LeftAdjustment()  override;
	virtual void BackwardAdjustment()  override;

	virtual void ShowSelection() override;
	virtual void SetAdjustmentType(SelectedObject::adjustment) override;
	virtual void SnapToObject() override;
	virtual void Duplicate() override;
	virtual void Erase() override;
	virtual void DrawUI() override;

private:
	PositionUI* position_ui;
	RotationUI* rotation_ui;
	ScaleUI* scale_ui;

};

#endif _activeobject
#pragma once
