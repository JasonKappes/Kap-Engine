#include "EditorUpdate.h"
#include "KeyboardEventManager.h"
#include "SerializableManager.h"
#include "WorldEditorManager.h"
#include "MouseEventManager.h"

void EditorUpdate::Tick() const
{
	this->m_keyboardEventManager->ProcessSingleKeyEvents();

	this->m_MouseEventManager->ProcessSingleMouseEvents();
}

EditorUpdate::EditorUpdate(const KeyboardEventManager& km, const MouseEventManager& mm)
{
	m_keyboardEventManager = &km;
	m_MouseEventManager    = &mm;
}
