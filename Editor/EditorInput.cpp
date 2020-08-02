#include "EditorInput.h"
#include "InputableAttorney.h"
#include "TouchableAttorney.h"
#include "SelectedObject.h"
#include "SceneAttorney.h"
#include "EmptyObject.h"
#include "ActiveObject.h"
#include "RollbackHandlerAttorney.h"
#include "SceneManager.h"

EditorInput::EditorInput()
{
	//create selection objects upfront to avoid duplicates
	activeObject	= new ActiveObject();
	emptyObject		= new EmptyObject();

	//set starting selection object
	selectedObject  = emptyObject;
	this->UIselected = false;

	//register user editor input
	InputableAttorney::Registration::FastKeyRegistration(this, AZUL_KEY::KEY_Z, EVENT_TYPE::HELD_DOWN);
	InputableAttorney::Registration::FastKeyRegistration(this, AZUL_KEY::KEY_1, EVENT_TYPE::PRESS);
	InputableAttorney::Registration::FastKeyRegistration(this, AZUL_KEY::KEY_2, EVENT_TYPE::PRESS);
	InputableAttorney::Registration::FastKeyRegistration(this, AZUL_KEY::KEY_3, EVENT_TYPE::PRESS);
	InputableAttorney::Registration::FastKeyRegistration(this, AZUL_KEY::KEY_P, EVENT_TYPE::PRESS);
	InputableAttorney::Registration::FastKeyRegistration(this, AZUL_KEY::KEY_V, EVENT_TYPE::PRESS);
	InputableAttorney::Registration::FastKeyRegistration(this, AZUL_KEY::KEY_ENTER, EVENT_TYPE::PRESS);
	InputableAttorney::Registration::FastKeyRegistration(this, AZUL_KEY::KEY_DELETE, EVENT_TYPE::PRESS);

	TouchableAttorney::Registration::FastMouseRegistration(this, AZUL_MOUSE::BUTTON_LEFT, MOUSE_EVENT_TYPE::PRESS);
	TouchableAttorney::Registration::FastMouseRegistration(this, AZUL_MOUSE::BUTTON_LEFT, MOUSE_EVENT_TYPE::RELEASE);

	TouchableAttorney::Registration::FastMouseRegistration(this, AZUL_MOUSE::CURSOR_MOVEMENT_DOWN, MOUSE_EVENT_TYPE::CURSOR_DIRECTION);
	TouchableAttorney::Registration::FastMouseRegistration(this, AZUL_MOUSE::CURSOR_MOVEMENT_UP, MOUSE_EVENT_TYPE::CURSOR_DIRECTION);
	TouchableAttorney::Registration::FastMouseRegistration(this, AZUL_MOUSE::CURSOR_MOVEMENT_LEFT, MOUSE_EVENT_TYPE::CURSOR_DIRECTION);
	TouchableAttorney::Registration::FastMouseRegistration(this, AZUL_MOUSE::CURSOR_MOVEMENT_RIGHT, MOUSE_EVENT_TYPE::CURSOR_DIRECTION);

}

void EditorInput::KeyHeld(AZUL_KEY t_key)
{
	switch (t_key)
	{
	case AZUL_KEY::KEY_Z:
		RollbackHandlerAttorney::Rollback();
		break;
	default:
		break;
	}
}

void EditorInput::KeyPressed(AZUL_KEY key)
{
	switch (key)
	{
	case AZUL_KEY::KEY_1:
		selectedObject->SetAdjustmentType(SelectedObject::adjustment::position);
		break;
	case AZUL_KEY::KEY_2:
		selectedObject->SetAdjustmentType(SelectedObject::adjustment::rotation);
		break;
	case AZUL_KEY::KEY_3:
		selectedObject->SetAdjustmentType(SelectedObject::adjustment::scale);
		break;
	case AZUL_KEY::KEY_P:
		selectedObject->SnapToObject();
		break;
	case AZUL_KEY::KEY_ENTER:
		SceneAttorney::Registration::GetSerializableMgr()->SelectNewlyLoadedObjects(this);
		selectedObject->SnapToObject();
		break;
	case AZUL_KEY::KEY_V:
		selectedObject->Duplicate();
		break;
	case AZUL_KEY::KEY_DELETE:
		selectedObject->Erase();
		selectedObject = this->emptyObject;
		break;
	default:
		break;
	}
}

void EditorInput::MouseActionReleased(AZUL_MOUSE t_mouseaction)
{
	switch (t_mouseaction)
	{
	case AZUL_MOUSE::BUTTON_LEFT:
		if (UIselected == false)
		{
			selectedObject->DisableIndicators();
			selectedObject->SetEmptyUI();
			SceneAttorney::Registration::GetSerializableMgr()->MousePick(this);
		}
		else {
			selectedObject->SetEmptyIndicator();
		}
		break;
	default:
		break;
	}
}

void EditorInput::MouseActionPressed(AZUL_MOUSE t_key)
{
	switch (t_key)
	{
	case AZUL_MOUSE::BUTTON_LEFT:
		UIselected = false;
		SceneAttorney::Registration::GetSelectableManager()->ProcessSelections(this);
		break;
	default:
		break;
	}
}

void EditorInput::MouseDirection(AZUL_MOUSE direction)
{
	switch (direction)
	{
	case AZUL_MOUSE::CURSOR_MOVEMENT_DOWN:
		selectedObject->BackwardAdjustment();
		break;
	case AZUL_MOUSE::CURSOR_MOVEMENT_UP:
		selectedObject->ForwardAdjustment();
		break;
	case AZUL_MOUSE::CURSOR_MOVEMENT_LEFT:
		selectedObject->LeftAdjustment();
		break;
	case AZUL_MOUSE::CURSOR_MOVEMENT_RIGHT:
		selectedObject->RightAdjustment();
		break;
	default:
		break;
	}
}

void EditorInput::VisualizeSelection()
{
	this->selectedObject->ShowSelection();
	this->selectedObject->DrawUI();
}

void EditorInput::SetActiveSelection(Serializable* t_selectedObject)
{
	this->selectedObject = activeObject;
	this->selectedObject->SetObjectForAdjustment(t_selectedObject);
	this->selectedObject->SetAdjustmentType(SelectedObject::adjustment::position);
}

void EditorInput::SetEmptySelection()
{
	this->selectedObject = emptyObject;
}

EditorInput::~EditorInput()
{
	delete this->activeObject;
	delete this->emptyObject;
}
