#ifndef _touchableattorney
#define _touchableattorney
#include "MouseEventManager.h"

class Touchable;

class TouchableAttorney
{
public:
	class GameLoop
	{
		friend class SingleMouseClickManager;
		friend class SingleMouseMotionManager;
	private:
		static void MouseActionPress(Touchable*, AZUL_MOUSE);
		static void MouseActionRelease(Touchable*, AZUL_MOUSE);
		static void MouseActionHeld(Touchable*, AZUL_MOUSE);
		static void MouseDirection(Touchable*, AZUL_MOUSE);

	private:
		GameLoop() = delete;
		GameLoop(const GameLoop&) = delete;
		GameLoop operator=(const GameLoop&) = delete;
		~GameLoop() = delete;
	};

public:
	class Registration
	{
		friend class TouchRegistrationCommand;
		friend class TouchDeRegistrationCommand;
		friend class EditorInput;
	private:
		static void FastMouseRegistration(Touchable*, AZUL_MOUSE, MOUSE_EVENT_TYPE);
		static void MouseRegistration(Touchable*, AZUL_MOUSE, MOUSE_EVENT_TYPE);
		static void MouseDeRegistration(Touchable*, AZUL_MOUSE, MOUSE_EVENT_TYPE);

	private:
		Registration() = delete;
		Registration(const Registration&) = delete;
		Registration operator=(const Registration&) = delete;
		~Registration() = delete;
	};

private:
	TouchableAttorney() = delete;
	TouchableAttorney(const TouchableAttorney&) = delete;
	TouchableAttorney operator=(const TouchableAttorney&) = delete;
	~TouchableAttorney() = delete;
};

#endif _touchableattorney
#pragma once
