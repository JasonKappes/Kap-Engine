#ifndef _spritefontmanager
#define _spritefontmanager
#include <map>
#include <string>

class KapSprite;
class SpriteFont;

//manages sprite resources
class SpriteFontManager
{
	friend class SpriteFontManagerAttorney;
public: /// ----> USER METHODS

	/// Loads a 2D sprite/image
	/// Takes a user-defined sprite name and a user-defined path to load the sprite. To be called from LoadAllResources.cpp
	static void Load(const char* t_chosenName , const char* t_fileName) { Instance().privLoad(t_chosenName, t_fileName); }

	/// Retrieves a Sprite-style Font for use by a sprite string.
	/// Takes a user-defined path to the sprite font as input.
	static SpriteFont* Get(const char* t_fileName) { return Instance().privGet(t_fileName); }

public:
	/// A default sprite font to load is Dosis2. Load this font (to use for a SpriteString) in LoadAllResources.cpp.
	/// Default Key Syntax: 	SpriteFontManager::Load("Fonts/Dosis2", "Fonts/Dosis2");
	static std::string defaultKeyAsset;

private:
	static void Delete() { Instance().privDelete(); }

private:
	SpriteFontManager() = default;
	SpriteFontManager(const SpriteFontManager&) = delete;
	SpriteFontManager operator=(const SpriteFontManager&) = delete;
	~SpriteFontManager() = default;

	static SpriteFontManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!m_ptrInstance)
			m_ptrInstance = new SpriteFontManager;
		return *m_ptrInstance;
	};

	void privDelete();
	void privLoad(const char*,const char*);
	SpriteFont* privGet(const char*);

private:
	static SpriteFontManager* m_ptrInstance;
	std::map<std::string, SpriteFont*> m_fontMap;
};

#endif _spritefontmanager
#pragma once
