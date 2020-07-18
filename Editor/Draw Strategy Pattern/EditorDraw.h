#ifndef _editordraw
#define _editordraw
#include "SystemUpdate.h"
#include "SerializableManager.h"
#include "WorldEditorManager.h"

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
