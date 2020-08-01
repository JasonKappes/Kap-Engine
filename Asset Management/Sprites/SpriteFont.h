#ifndef _SpriteFont
#define _SpriteFont
#include <map.>
#include <string>
#include <xmllite.h>
#include <list>

class KapSprite;
class Texture;

// A SpriteFont holds all of the glyphs associated with a font-type
class SpriteFont
{
public:
	using Key = int;
	using Glyph = KapSprite;

private:
	using FontMap = std::map< Key, Glyph* >;
	using FontMapIt = FontMap::iterator;

public:
	//returns a sprite of the given character input
	Glyph* GetGlyph(char c);

public:
	SpriteFont() = delete;
	SpriteFont(std::string path);
	SpriteFont(const SpriteFont&) = delete;
	SpriteFont& operator=(const SpriteFont&) = delete;
	~SpriteFont();

private: // --- >  ENGINE METHODS
	void XMLtoCollection(std::string filename);
	void ElementTextToInt(IXmlReader* pReader, int& out);

private:
	std::string Name;
	Texture* FontTexture;
	FontMap fontmap;
};

#endif _SpriteFont
