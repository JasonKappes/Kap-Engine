#ifndef _editorupdate
#define _editorupdate
#include "SystemUpdate.h"

class KeyboardEventManager;
class MouseEventManager;

class EditorUpdate : public SystemUpdate
{
public:
	EditorUpdate() = delete;
	EditorUpdate(const EditorUpdate&) = delete;
	EditorUpdate operator=(const EditorUpdate&) = delete;
	~EditorUpdate() = default;

	EditorUpdate(const KeyboardEventManager&, const MouseEventManager&);

protected:
	void Tick() const override;

private:
	const KeyboardEventManager* m_keyboardEventManager;
	const MouseEventManager*    m_MouseEventManager;

};

#endif _editorupdate
#pragma once
