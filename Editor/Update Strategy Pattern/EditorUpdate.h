#ifndef _editorupdate
#define _editorupdate
#include "SystemUpdate.h"

class KeyboardEventManager;
class MouseEventManager;

//(Strategy Pattern object): This defines what systems are updated during world-edit mode.
class EditorUpdate : public SystemUpdate
{
public:
	EditorUpdate() = delete;
	EditorUpdate(const EditorUpdate&) = delete;
	EditorUpdate operator=(const EditorUpdate&) = delete;
	~EditorUpdate() = default;

	EditorUpdate(const KeyboardEventManager&, const MouseEventManager&);

protected:
	//Keyboard and mouse events are looked for.
	void Tick() const override;

private:
	const KeyboardEventManager* m_keyboardEventManager;
	const MouseEventManager*    m_MouseEventManager;

};

#endif _editorupdate
#pragma once
