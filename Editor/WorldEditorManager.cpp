#include "WorldEditorManager.h"
#include "CameraManager.h"
#include "EditorInput.h"

WorldEditorManager::WorldEditorManager(CameraManager* cm)
{
	this->editorInput = new EditorInput();

	cm->DefaultTopdownView();
}

void WorldEditorManager::SendVisualizeRequests() const
{
	this->editorInput->VisualizeSelection();
}

WorldEditorManager::~WorldEditorManager()
{
	delete this->editorInput;
}
