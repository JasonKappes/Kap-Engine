#include "TouchableAttorney.h"
#include "Touchable.h"

void TouchableAttorney::Registration::FastMouseRegistration(Touchable* t_touchable, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event)
{
	t_touchable->FastMouseRegistration(t_key, t_event);
}

void TouchableAttorney::Registration::MouseRegistration(Touchable* t_touchable, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event)
{
	t_touchable->MouseRegistration(t_key, t_event);
}

void TouchableAttorney::Registration::MouseDeRegistration(Touchable* t_touchable, AZUL_MOUSE t_key, MOUSE_EVENT_TYPE t_event)
{
	t_touchable->MouseDeRegistration(t_key, t_event);
}

void TouchableAttorney::GameLoop::MouseActionPress(Touchable* t_touchable, AZUL_MOUSE t_key)
{
	t_touchable->MouseActionPressed(t_key);
}

void TouchableAttorney::GameLoop::MouseActionHeld(Touchable* t_touchable, AZUL_MOUSE t_key)
{
	t_touchable->MouseActionHeld(t_key);
}

void TouchableAttorney::GameLoop::MouseActionRelease(Touchable* t_touchable, AZUL_MOUSE t_key)
{
	t_touchable->MouseActionReleased(t_key);
}

void TouchableAttorney::GameLoop::MouseDirection(Touchable* t_touchable, AZUL_MOUSE t_key)
{
	t_touchable->MouseDirection(t_key);
}

