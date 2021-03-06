#ifndef _editordraw
#define _editordraw
#include "SystemUpdate.h"
#include "SerializableManager.h"
#include "WorldEditorManager.h"

//If the EDITOR MODE is enabled, a this is the Draw mode chosen to only render serializable objects
class EditorDraw : public SystemUpdate
{
public:
	EditorDraw() = default;
	EditorDraw(const EditorDraw&) = delete;
	~EditorDraw() = default;

	EditorDraw(const SerializableManager& s, const WorldEditorManager& w) 
	{ 
		serializableManager = &s;

		worldEditorManager = &w;
	}

	void Tick() const override 
	{ 
		serializableManager->EditorDraw(); 

		worldEditorManager->SendVisualizeRequests();
	}

private:
	const SerializableManager* serializableManager;
	const WorldEditorManager* worldEditorManager;
};

#endif _editordraw
#pragma once
