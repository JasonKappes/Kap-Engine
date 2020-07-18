#include "Cursor.h"
#include "CursorPosition.h"

Cursor* Cursor::m_ptrInstance = nullptr;

Cursor::Cursor() : m_prevMousePosition(new CursorPosition),
m_currMousePosition(new CursorPosition), m_upMovementDistance(0), m_downMovementDistance(0),
m_leftMovementDistance(0), m_rightMovementDistance(0) {}

Cursor::~Cursor() 
{ 
	delete this->m_prevMousePosition; 
	delete this->m_currMousePosition;
}

void Cursor::Terminate()
{
	delete Instance().m_ptrInstance;
}

void Cursor::privProcessMovements()
{
	m_prevMousePosition->x = m_currMousePosition->x;
	m_prevMousePosition->y = m_currMousePosition->y;

	KapEngine::GetMousePosition(m_currMousePosition->x, m_currMousePosition->y);
}

void Cursor::GetCursorCoordinates(int& x, int& y)
{
	KapEngine::getMousePosition(x, y);
}

void Cursor::GetCursorBounds(int& xBound, int& yBound)
{
	xBound = KapEngine::GetWindowWidth();
	yBound = KapEngine::GetWindowHeight();
}

bool Cursor::privGetMouseMovement(AZUL_MOUSE m)
{
	switch(m)
	{
		case(AZUL_MOUSE::CURSOR_MOVEMENT_UP):
			return isUpCursorMovement();
			break;
		case(AZUL_MOUSE::CURSOR_MOVEMENT_DOWN):
			return isDownCursorMovement();
			break;
		case(AZUL_MOUSE::CURSOR_MOVEMENT_RIGHT):
			return isRightCursorMovement();
			break;
		case(AZUL_MOUSE::CURSOR_MOVEMENT_LEFT):
			return isLeftCursorMovement();
			break;
		default:
			return false;
			break;
	}
}

bool Cursor::isUpCursorMovement()
{
	if (m_prevMousePosition->y > m_currMousePosition->y)
	{
		this->m_upMovementDistance = m_prevMousePosition->y - m_currMousePosition->y;
		return true;
	}
	else {
		this->m_upMovementDistance = 0;
		return false;
	}
}

bool Cursor::isDownCursorMovement()
{
	if (m_prevMousePosition->y < m_currMousePosition->y)
	{
		this->m_downMovementDistance = m_currMousePosition->y - m_prevMousePosition->y;
		return true;
	}
	else {
		this->m_downMovementDistance = 0;
		return false;
	}
}

bool Cursor::isRightCursorMovement()
{
	if (m_prevMousePosition->x < m_currMousePosition->x)
	{
		this->m_rightMovementDistance = m_currMousePosition->x - m_prevMousePosition->x;
		return true;
	}
	else {
		this->m_rightMovementDistance = 0;
		return false;
	}
}

bool Cursor::isLeftCursorMovement()
{
	if (m_prevMousePosition->x > m_currMousePosition->x)
	{
		this->m_leftMovementDistance = m_prevMousePosition->x - m_currMousePosition->x;
		return true;
	}
	else {
		this->m_leftMovementDistance = 0;
		return false;
	}
}

int Cursor::GetUpCursorMovementAmount()			{ return Instance().m_upMovementDistance;	}

int Cursor::GetDownCursorMovementAmount()		{ return Instance().m_downMovementDistance; }

int Cursor::GetLeftCursorMovementAmount()		{ return Instance().m_leftMovementDistance; }

int Cursor::GetRightCursorMovementAmount()		{ return Instance().m_rightMovementDistance;}

