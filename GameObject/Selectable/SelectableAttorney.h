#ifndef _selectableattorney
#define _selectableattorney
#include "Selectable.h"

class Touchable;

class SelectableAttorney
{

public:
	class Registration
	{
		friend class SelectionRegistrationCommand;
		friend class SelectionDeRegistrationCommand;
	private:
		static void SceneRegistration(Selectable*);
		static void SceneDeRegistration(Selectable*);

	private:
		Registration() = delete;
		Registration(const Registration&) = delete;
		Registration operator=(const Registration&) = delete;
		~Registration() = delete;
	};

	class Editor
	{
		friend class xPosUI;
		friend class zPosUI;
		friend class yPosUI;
		friend class xRotUI;
		friend class yRotUI;
		friend class zRotUI;
		friend class xyzScaleUI;
		friend class WorldUI;
	private:
		static void FastSceneRegistration(Selectable*);
		static void FastSceneDeRegistration(Selectable*);
		static void SetSelectionModel(Selectable*, Selectable::Volume chosenCollisionVolume = Selectable::Volume::BSPHERE);
	private:
		Editor() = delete;
		Editor(const Editor&) = delete;
		Editor operator=(const Editor&) = delete;
		~Editor() = delete;
		
	};

private:
	SelectableAttorney() = delete;
	SelectableAttorney(const SelectableAttorney&) = delete;
	SelectableAttorney operator=(const SelectableAttorney&) = delete;
	~SelectableAttorney() = delete;
};

#endif _selectableattorney
#pragma once
