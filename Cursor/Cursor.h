#ifndef _cursor
#define _cursor
#include "KapEngine.h"

class CursorPosition;

//Singleton: Provides access to various information relating to the cursor every frame
class Cursor
{
	friend class CursorAttorney;

public: // --> USER METHODS
	
	//Returns the distance the cursor moved up last frame
	static int GetUpCursorMovementAmount();
	
	//Returns the distance the cursor moved down last frame
	static int GetDownCursorMovementAmount();
	
	//Returns the distance the cursor moved left last frame
	static int GetLeftCursorMovementAmount();
	
	//Returns the distance the cursor moved right last frame
	static int GetRightCursorMovementAmount();
	
	//Returns the cursor coordinates on the game window
	static void GetCursorCoordinates(int& x, int& y);

	//Returns the distance the cursor can go on the X and Y axis
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
