#include "InputableAttorney.h"
#include "Inputable.h"

void InputableAttorney::Registration::FastKeyRegistration(Inputable* t_inputable, AZUL_KEY t_key, EVENT_TYPE t_event)
{
	t_inputable->FastKeyRegistration(t_key, t_event);
}

void InputableAttorney::Registration::FastKeyDeRegistration(Inputable* t_inputable, AZUL_KEY t_key, EVENT_TYPE t_event)
{
	t_inputable->FastKeyDeRegistration(t_key, t_event);
}

void InputableAttorney::Registration::KeyRegistration(Inputable* t_inputable, AZUL_KEY t_key, EVENT_TYPE t_event)
{
	t_inputable->KeyRegistration(t_key, t_event);
}

void InputableAttorney::Registration::KeyDeRegistration(Inputable* t_inputable, AZUL_KEY t_key, EVENT_TYPE t_event)
{
	t_inputable->KeyDeRegistration(t_key, t_event);
}

void InputableAttorney::GameLoop::KeyPress(Inputable* t_inputable, AZUL_KEY t_key)
{
	t_inputable->KeyPressed(t_key);
}

void InputableAttorney::GameLoop::KeyHeld(Inputable* t_inputable, AZUL_KEY t_key)
{
	t_inputable->KeyHeld(t_key);
}

void InputableAttorney::GameLoop::KeyRelease(Inputable* t_inputable, AZUL_KEY t_key)
{
	t_inputable->KeyReleased(t_key);
}

