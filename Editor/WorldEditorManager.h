#ifndef _worldeditormanager
#define _worldeditormanager

class EditorInput;
class CameraManager;

class WorldEditorManager
{
public:
	WorldEditorManager() = delete;
	WorldEditorManager(CameraManager*);
	WorldEditorManager(const WorldEditorManager&) = delete;
	WorldEditorManager operator=(const WorldEditorManager&) = delete;
	~WorldEditorManager();

	void SendVisualizeRequests() const;

private:
	EditorInput* editorInput;
};

#endif _worldeditormanager
#pragma once
