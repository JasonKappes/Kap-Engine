#ifndef _cursorattorney
#define _cursorattorney
#include "Cursor.h"

//Helps manage access to Cursor Singleton
class CursorAttorney
{
	friend class KapEngine;
	friend class SingleMouseMotionManager;
private:

	static void ProcessCursorMovement()			{ Cursor::ProcessMovements(); }
	static void Delete()						{ Cursor::Terminate(); }
	static bool GetMouseMovement(AZUL_MOUSE m)	{ return Cursor::GetMouseMovement(m); }

private:
	CursorAttorney() = delete;
	CursorAttorney(const CursorAttorney&) = delete;
	CursorAttorney operator=(const CursorAttorney&) = delete;
	~CursorAttorney() = delete;
};

#endif _cursorattorney
#pragma once
