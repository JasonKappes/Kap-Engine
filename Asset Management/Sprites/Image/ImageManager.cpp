#include "ImageManager.h"
#include <DebugOut.h>

ImageManager* ImageManager::m_ptrInstance = nullptr;

std::string ImageManager::defaultKeyAsset = "DefaultAssets/stitch.tga";

void ImageManager::Delete()
{
	StorageMap::iterator it;
	Image* t_delImg;
	for (it = Instance().m_storageMap.begin(); it != Instance().m_storageMap.end(); ++it)
	{
		t_delImg = it->second;
		delete it->second;
	}
	Instance().m_storageMap.clear();

	DebugMsg::out("\n IMAGE MANAGER DESTRUCTOR ----> %d images left", Instance().m_storageMap.size());
	delete ImageManager::m_ptrInstance;
}

Image* ImageManager::Get(const MapKey& t_mapKey)
{
	return Instance().m_storageMap.find(t_mapKey)->second;
}

void ImageManager::Load(const MapKey& t_mapKey, Texture* t_texture)
{
	try
	{
		if (Instance().m_storageMap.at(t_mapKey) != NULL) {			//check if image has been added
			throw std::runtime_error(" ERROR: Duplicate image (ID: " + (std::string)t_mapKey + ") loaded. ");
		}
	}
	catch (std::out_of_range exc) {		// if not, then add it		
		Image* t_image = new Image(t_texture, new Rect(0, 0, (float)t_texture->getWidth(), (float)t_texture->getHeight()));
		Instance().m_storageMap.insert({ t_mapKey, t_image });
	}
}

void ImageManager::Load(const MapKey& t_mapKey, Texture* t_texture, Rect* t_rect)
{
	try
	{
		if (Instance().m_storageMap.at(t_mapKey) != NULL) {			//check if image has been added
			throw std::runtime_error(" ERROR: Duplicate image (ID: " + (std::string)t_mapKey + ") loaded. ");
		}
	}
	catch (std::out_of_range exc) {		// if not, then add it		
		Image* t_image = new Image(t_texture, new Rect(*t_rect));
		Instance().m_storageMap.insert({ t_mapKey, t_image });
	}
}

