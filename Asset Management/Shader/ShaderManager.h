#ifndef _shadermanager
#define _shadermanager
#include <map>
#include <iostream>
#include <string>

class ShaderObject;
class PreMadeModels;

class ShaderManager
{
	friend class ShaderManagerAttorney;
public: // ----> USER METHODS

	/// <summary>
	/// Loads a shader for use by a GameObject.
	/// 
	/// Takes a user-defined path to the shader as input. To be called from LoadAllResources.cpp
	/// </summary> 
	/// \ingroup ShaderManager
	static void Load(const char* t_fileName) { Instance().privLoad(t_fileName); }

	/// <summary>
	/// Called from a GameObject to retrieve a loaded shader
	/// </summary> 
	/// \ingroup ShaderManager
	static ShaderObject* Get(const char* t_fileName) { return Instance().privGet(t_fileName); }

public:
	/// <summary>
	/// A default sprite font to load is Dosis2. Load this font (to use for a SpriteString) in LoadAllResources.cpp.
	/// 
	/// Default Key Syntax: 	ShaderManager::Load("DefaultAssets/textureFlatRender");
	/// </summary> 
	/// \ingroup ShaderManager
	static std::string defaultKeyAsset;

private:
	ShaderManager() = default;
	ShaderManager(const ShaderManager&) = delete;
	ShaderManager operator=(const ShaderManager&) = delete;
	~ShaderManager() = default;

	static ShaderManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!m_ptrInstance)
			m_ptrInstance = new ShaderManager;
		return *m_ptrInstance;
	};

	static void Delete() { Instance().privDelete(); }
	void privLoad(const char* t_fileName);
	ShaderObject* privGet(const char* t_fileName);
	void privDelete();

private:
	static ShaderManager* m_ptrInstance;
	std::map<std::string, ShaderObject*> m_shaderMap;

};

#endif _shadermanager
#pragma once

