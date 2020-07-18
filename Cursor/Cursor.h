#ifndef _cursor
#define _cursor
#include "KapEngine.h"

class CursorPosition;

class Cursor
{
	friend class CursorAttorney;

public: //USER METHODS

	static int GetUpCursorMovementAmount();
	static int GetDownCursorMovementAmount();
	static int GetLeftCursorMovementAmount();
	static int GetRightCursorMovementAmount();

	static void GetCursorCoordinates(int& x, int& y);

	static void GetCursorBounds(int& xBound, int& yBound);
	
private:
	Cursor();
	Cursor(const Cursor&) = delete;
	Cursor operator=(const Cursor&) = delete;
	~Cursor();

	static Cursor& Instance()
	{
		if (!m_ptrInstance)
		{
			m_ptrInstance = new Cursor();
		}
		return *m_ptrInstance;
	}

	static void ProcessMovements()			   { Instance().privProcessMovements(); }
	static bool GetMouseMovement(AZUL_MOUSE m) { return Instance().privGetMouseMovement(m); }
	static void Terminate();

	void privProcessMovements();
	bool privGetMouseMovement(AZUL_MOUSE);

	bool isUpCursorMovement();
	bool isDownCursorMovement();
	bool isLeftCursorMovement();
	bool isRightCursorMovement();

private:
	static Cursor* m_ptrInstance;

	CursorPosition* m_prevMousePosition;
	CursorPosition* m_currMousePosition;

	int m_upMovementDistance;
	int m_downMovementDistance;
	int m_leftMovementDistance;
	int m_rightMovementDistance;
};


#endif _cursor
#pragma once
