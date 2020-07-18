#include "ActiveObject.h"
#include "Serializable.h"
#include "VisualizerAttorney.h"
#include "Color.h"
#include "RollbackHandlerAttorney.h"
#include "ReviveSerializableCommand.h"
#include "SerializableManager.h"
#include "PositionUI.h"
#include "RotationUI.h"
#include "ScaleUI.h"
#include "EmptyUI.h"

ActiveObject::ActiveObject()
{
	position_ui = new PositionUI();
	rotation_ui = new RotationUI();
	scale_ui	= new ScaleUI();
	
	active_ui = empty_ui;
}

void ActiveObject::ForwardAdjustment()
{
	assert(selectedObject != nullptr);

	this->active_ui->GetSelectedIndicator().ForwardMovement(selectedObject);
}

void ActiveObject::RightAdjustment()
{
	assert(selectedObject != nullptr);

	this->active_ui->GetSelectedIndicator().RightMovement(selectedObject);
}

void ActiveObject::LeftAdjustment()
{
	assert(selectedObject != nullptr);

	this->active_ui->GetSelectedIndicator().LeftMovement(selectedObject);
}

void ActiveObject::BackwardAdjustment()
{
	assert(selectedObject != nullptr);

	this->active_ui->GetSelectedIndicator().BackwardMovement(selectedObject);
}

void ActiveObject::ShowSelection()
{
	Vect center = SerializableAttorney::GameLoop::GetTransform(this->selectedObject)->GetCenter();

	float radius = SerializableAttorney::GameLoop::GetTransform(this->selectedObject)->GetRadius();

	active_ui->UpdateUI(radius, center);
}

void ActiveObject::DrawUI()
{
	active_ui->DrawUI();
}

void ActiveObject::SnapToObject()
{
	Vect pos = SerializableAttorney::GameLoop::GetTransform(selectedObject)->position;

	SceneAttorney::Registration::GetCameraManager()->SnapToObject(pos);
}

void ActiveObject::Duplicate()
{
	SerializableAttorney::GameLoop::Duplicate(*this->selectedObject);
}

void ActiveObject::Erase()
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(selectedObject);

	RollbackHandlerAttorney::LogEvent(new ReviveSerializableCommand(*selectedObject, *new Transform(*t)));

	SerializableAttorney::GameLoop::Remove(this->selectedObject);
}

ActiveObject::~ActiveObject()
{
	delete position_ui;
	delete rotation_ui;
	delete scale_ui;
}

void ActiveObject::SetAdjustmentType(SelectedObject::adjustment type)
{
	switch (type)
	{
	case(SelectedObject::adjustment::position):
		//reset curr UI
		DisableIndicators();
		active_ui->EmptyIndicatorSelected();

		active_ui = this->position_ui;
		this->position_ui->EnableIndicator();
		break;
	case(SelectedObject::adjustment::rotation):
		//reset curr UI
		DisableIndicators();
		active_ui->EmptyIndicatorSelected();

		active_ui = this->rotation_ui;
		this->rotation_ui->EnableIndicator();
		break;
	case(SelectedObject::adjustment::scale):
		//reset curr UI
		DisableIndicators();
		active_ui->EmptyIndicatorSelected();

		active_ui = this->scale_ui;
		this->scale_ui->EnableIndicator();
		break;
	case(SelectedObject::adjustment::none):
		active_ui->ResetIndicator();
		this->SetEmptyIndicator();
		break;
	default:
		break;
	}
}
