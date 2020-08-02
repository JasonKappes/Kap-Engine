#ifndef _worldeditormanager
#define _worldeditormanager

class EditorInput;
class CameraManager;

//This manager is only created during world edit mode. 
//It manages any world-edit resources (just the editor input object)
class WorldEditorManager
{
public:
	WorldEditorManager() = delete;
	WorldEditorManager(CameraManager*);
	WorldEditorManager(const WorldEditorManager&) = delete;
	WorldEditorManager operator=(const WorldEditorManager&) = delete;
	~WorldEditorManager();

	//Calls the editor input object to display any indicators around a selected object
	void SendVisualizeRequests() const;

private:
	EditorInput* editorInput;
};

#endif _worldeditormanager
#pragma once
