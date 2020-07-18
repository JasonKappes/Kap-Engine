#ifndef _spritestring
#define _spritestring
#include "SpriteFont.h"
#include <vector>

class SpriteString
{
public:

	/// <summary>
	/// This method should be called on a SpriteString object from Draw2D() to show this text on screen.
	/// </summary> 
	/// \ingroup SpriteString
	void Render();

	/// <summary>
	/// Returns the pixel height of the SpriteString.
	/// </summary> 
	/// \ingroup SpriteString
	int GetHeight();

	/// <summary>
	/// Returns the pixel width of the SpriteString.
	/// </summary> 
	/// \ingroup SpriteString
	int GetWidth();

	/// <summary>
	/// Sets the position of the SpriteString when shown on screen.
	/// </summary> 
	/// \ingroup SpriteString
	void SetPosition(int xPosition, int yPosition);

public:
	SpriteString() = delete;
	SpriteString(SpriteFont* font, std::string text, int x, int y);
	SpriteString(const SpriteString&) = delete;
	SpriteString operator= (const SpriteString&) = delete;
	~SpriteString();

private:
	//called from the constructor
	void Set(SpriteFont& font, std::string phrase, int x, int y);

private:
	std::vector<SpriteFont::Glyph*>* m_glyphCollection;

	int m_posX;
	int m_posY;
	int m_width;
	int m_height;
	int m_size;

	const float customTweak = 1.5f;
};

#endif _spritestring
#pragma once
