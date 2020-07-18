#ifndef _inputableattorney
#define _inputableattorney
#include "KeyboardEventManager.h"
#include <AzulCore.h>

class Inputable;

class InputableAttorney
{
public:
	class GameLoop
	{
		friend class SingleKeyEventManager;
	private:
		static void KeyPress(Inputable*, AZUL_KEY);
		static void KeyRelease(Inputable*, AZUL_KEY);
		static void KeyHeld(Inputable*, AZUL_KEY);

	private:
		GameLoop() = delete;
		GameLoop(const GameLoop&) = delete;
		GameLoop operator=(const GameLoop&) = delete;
		~GameLoop() = delete;
	};

public:
	class Registration
	{
		friend class InputRegistrationCommand;
		friend class InputDeRegistrationCommand;
		friend class EditorInput;
		friend class GodCam;
	private:
		static void FastKeyRegistration(Inputable*, AZUL_KEY, EVENT_TYPE);
		static void FastKeyDeRegistration(Inputable*, AZUL_KEY, EVENT_TYPE);
		static void KeyRegistration(Inputable*, AZUL_KEY, EVENT_TYPE);
		static void KeyDeRegistration(Inputable*, AZUL_KEY, EVENT_TYPE);

	private:
		Registration() = delete;
		Registration(const Registration&) = delete;
		Registration operator=(const Registration&) = delete;
		~Registration() = delete;
	};

private:
	InputableAttorney() = delete;
	InputableAttorney(const InputableAttorney&) = delete;
	InputableAttorney operator=(const InputableAttorney&) = delete;
	~InputableAttorney() = delete;
};

#endif _inputableattorney
#pragma once
