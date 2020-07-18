#include "SelectedObject.h"

SelectedObject::SelectedObject() : selectedObject(nullptr), empty_ui(new EmptyUI())
{
	active_ui = empty_ui;
}

SelectedObject::~SelectedObject() { delete empty_ui; }

void SelectedObject::SetObjectForAdjustment(Serializable* serializable)
{
	this->selectedObject = serializable;
}
