#ifndef _editorinput
#define _editorinput
#include "Inputable.h"
#include "Touchable.h"

class SelectedObject;
class Serializable;

//This object is created during world-edit mode. It manages input and object selection.
class EditorInput : public Inputable, public Touchable
{
public:
	EditorInput();
	EditorInput(const EditorInput&) = delete;
	EditorInput operator=(const EditorInput&) = delete;
	~EditorInput();

	//Callback for registered key presses
	void KeyPressed(AZUL_KEY) override;

	//Callback for registered key holds
	void KeyHeld(AZUL_KEY) override;
	
	//Callbacks for registered mouse action releases
	void MouseActionReleased(AZUL_MOUSE) override;

	//Callbacks for registered mouse action presses
	void MouseActionPressed(AZUL_MOUSE) override;

	//Callbacks for registered mouse movements
	void MouseDirection(AZUL_MOUSE) override;

	//If it has an object selected, it displays any active indicators
	void VisualizeSelection();

	//If an object is selected, it is sent to this object to be managed.
	void SetActiveSelection(Serializable*);
	
	//Switches strategy pattern objects to an "empty object" which isn't affect by any mouse/key input
	void SetEmptySelection();

private:
	SelectedObject* selectedObject;
	SelectedObject* activeObject;
	SelectedObject* emptyObject;

	bool UIselected;
};

#endif _editorinput
#pragma once
