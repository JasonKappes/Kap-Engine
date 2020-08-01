#include "SpriteString.h"
#include "KapSprite.h"
#include <DebugOut.h>

SpriteString::SpriteString(SpriteFont* font, std::string text, int x, int y)
{
	this->m_height = 0;
	this->m_width = 0;
	Set(*font, text, x, y);
}

//Renders each glyph in the sprite string
void SpriteString::Render()
{
	float lastWidth = (float)this->m_posX;
	std::vector<KapSprite*>::iterator it;

	for (int x = 0; x < (int)this->m_glyphCollection->size(); ++x)
	{
		(*this->m_glyphCollection)[x]->SetPosition(lastWidth, (float) this->m_posY);
		(*this->m_glyphCollection)[x]->Render();
		lastWidth += (*this->m_glyphCollection)[x]->GetWidth() / customTweak;
	}
}

int SpriteString::GetHeight()
{
	return this->m_height;
}

int SpriteString::GetWidth()
{
	return this->m_width;
}

void SpriteString::SetPosition(int t_newX, int t_newY)
{
	this->m_posX = t_newX;
	this->m_posY = t_newY;
}

//Sets the wording of a sprite string
void SpriteString::Set(SpriteFont& font, std::string phrase, int x, int y)
{
	this->m_glyphCollection = new std::vector<SpriteFont::Glyph*>();
	this->m_posX = x;
	this->m_posY = y;
	this->m_size = phrase.size();
	for (int pos = 0; pos < (int)phrase.size(); ++pos)
	{
		this->m_glyphCollection->push_back(font.GetGlyph(phrase[pos]));
		this->m_width += (int)this->m_glyphCollection->back()->GetWidth();
	}
	this->m_height = (int)this->m_glyphCollection->front()->GetHeight();
}

SpriteString::~SpriteString() { delete this->m_glyphCollection; }
