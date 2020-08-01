#ifndef _screenlog
#define _screenlog
#include <list>

class SpriteString;
class SpriteFont;

class ScreenLog
{
	friend class ScreenLogAttorney;
public: /// ---> USER METHODS

	/// Can be called by the player to print information in the top-left of the game window
	/// Recommended Syntax: ScreenLog::Add("message info: %d" , DataVariable);
	static void Add(char* A, ...);

private:

	ScreenLog();
	ScreenLog(const ScreenLog&) = delete;
	ScreenLog operator=(const ScreenLog&) = delete;
	~ScreenLog() = default;

	static ScreenLog& Instance()
	{
		if (!m_ptrInstance)
			m_ptrInstance = new ScreenLog();
		return *m_ptrInstance;
	}

	static void Delete();
	static void Render();
	void privRender();

private:
	static ScreenLog* m_ptrInstance;
	int m_anchorX;
	int m_anchorY;
	int m_verticalLineSpacing;
	char m_DebugBuff[256];
	SpriteFont* m_font;
	std::list<SpriteString*> m_messageCollection;
};

#endif _screenlog
#pragma once
