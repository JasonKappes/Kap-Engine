#ifndef _imagemanager
#define _imagemanager
#include <map>
#include <string>
#include "GraphicsObject_Sprite.h"
#include "Image.h"

class Texture;

class ImageManager
{
	friend class ImageManagerAttorney;
public:
	using MapKey = std::string;
	using StorageMap = std::map<std::string , Image*>;
public:

	/// Retrieves the associated image with user input.
	static Image* Get(const MapKey& ImageName);

	/// Loads a given texture and creates an associated user-named Image.
	static void Load(const MapKey& ImageName, Texture* textureName);

	/// Loads a given texture and creates an associated user-named Image with a user-defined size.
	static void Load(const MapKey& ImageName, Texture* textureName, Rect* portionToLoad);

public:
	/// A default image to load is stitch. Load this image (to use for a sprite) in LoadAllResources.cpp.
	/// Default Key Syntax: 	ImageManager::Load("stitchImage", TextureManager::Get("DefaultAssets/stitch.tga"));
	static std::string defaultKeyAsset;

private:
	ImageManager() = default;
	ImageManager(const ImageManager&) = delete;
	ImageManager operator=(const ImageManager&) = delete;
	~ImageManager() = default;

	static ImageManager& Instance()
	{
		if (!m_ptrInstance)
			m_ptrInstance = new ImageManager();
		return *m_ptrInstance;
	}

	static void Delete();

private:
	std::string m_defaultPath;
	StorageMap m_storageMap;
	static ImageManager* m_ptrInstance;


};

#endif _imagemanager
#pragma once
