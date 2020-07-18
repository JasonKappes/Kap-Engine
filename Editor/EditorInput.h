#ifndef _editorinput
#define _editorinput
#include "Inputable.h"
#include "Touchable.h"

class SelectedObject;
class Serializable;

class EditorInput : public Inputable, public Touchable
{
public:
	EditorInput();
	EditorInput(const EditorInput&) = delete;
	EditorInput operator=(const EditorInput&) = delete;
	~EditorInput();

	void Selection(Selectable*) override;

	void KeyPressed(AZUL_KEY) override;

	void KeyHeld(AZUL_KEY) override;
	
	void MouseActionReleased(AZUL_MOUSE) override;

	void MouseActionPressed(AZUL_MOUSE) override;

	void MouseDirection(AZUL_MOUSE) override;

	void VisualizeSelection();

	void SetActiveSelection(Serializable*);

	void SetEmptySelection();

private:
	SelectedObject* selectedObject;
	SelectedObject* activeObject;
	SelectedObject* emptyObject;

	bool UIselected;
};

#endif _editorinput
#pragma once
