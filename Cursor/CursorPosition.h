#ifndef _cursorposition
#define _cursorposition

class CursorPosition
{
public:
	CursorPosition() : x(0), y(0) {}
	CursorPosition(const CursorPosition&) = delete;
	CursorPosition operator=(const CursorPosition& c) = delete;
	~CursorPosition() = default;

public:
	int x;
	int y;
};

#endif _cursorposition
#pragma once
