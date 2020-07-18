 #ifndef _texturemanager
#define _texturemanager
#include <map>
#include <string>

class Texture;

class TextureManager
{
	friend class TextureManagerAttorney;
public: // ----> USER METHODS

	/// <summary>
	/// Loads a texture for use by a GameObject.
	/// 
	/// Takes a user-defined path to the texture as input. To be called from LoadAllResources.cpp
	/// </summary> 
	/// \ingroup TextureManager
	static void Load(const char* t_fileName) { Instance().privLoad(t_fileName); }

	/// <summary>
	/// Loads a texture for use by a GameObject.
	/// 
	/// Takes a user-defined path that names the custom color made from the three corresponding float inputs. To be called from LoadAllResources.cpp
	/// </summary> 
	/// \ingroup TextureManager
	static void Load(const char* t_fileName, unsigned char red, unsigned char green, unsigned char blue) { Instance().privLoad(t_fileName, red, green, blue); }

	/// <summary>
	/// Called from a GameObject to retrieve a loaded texture
	/// </summary> 
	/// \ingroup TextureManager
	static Texture* Get(const char* t_fileName) { return Instance().privGet(t_fileName); }

public:
	/// <summary>
	/// A default sprite font to load is Dosis2. Load this font (to use for a SpriteString) in LoadAllResources.cpp.
	/// 
	/// Default Key Syntax: 	TextureManager::Load("DefaultAssets/space_frigate.tga", "DefaultAssets/space_frigate.tga");
	/// </summary> 
	/// \ingroup TextureManager
	static std::string defaultKeyAsset;

private:
	TextureManager() = default;
	TextureManager(const TextureManager&) = delete;
	TextureManager operator=(const TextureManager&) = delete;
	~TextureManager() = default;

	static TextureManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!m_ptrInstance)
			m_ptrInstance = new TextureManager;
		return *m_ptrInstance;
	};

	static void Delete() { Instance().privDelete(); }

	void privLoad(const char* t_fileName);
	void privLoad(const char* t_fileName, unsigned char red, unsigned char green, unsigned char blue);
	Texture* privGet(const char* t_fileName);
	void privDelete();

private:
	static TextureManager* m_ptrInstance;
	std::map<std::string, Texture*> m_textureMap;

};

#endif _texturemanager
#pragma once
