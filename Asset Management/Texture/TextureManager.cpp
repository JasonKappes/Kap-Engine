#include "TextureManager.h"
#include "Texture.h"
#include <stdexcept>
#include <iostream>
#include <DebugOut.h>

TextureManager* TextureManager::m_ptrInstance = nullptr;

std::string TextureManager::defaultKeyAsset = "DefaultAssets/space_frigate.tga";

void TextureManager::privLoad(const char* t_fileName)
{
	try
	{
		if (this->m_textureMap.at(t_fileName) != NULL) {		//check if texture has been added
			throw std::runtime_error(" ERROR: Duplicate texture (ID: " + (std::string)t_fileName + ") loaded. ");

		} 	
	}
	catch (std::out_of_range exc) {		// if not, then add it

		this->m_textureMap[t_fileName] = new Texture(t_fileName);
		return;
	}
	return;
}

void TextureManager::privLoad(const char* t_fileName, unsigned char red, unsigned char green, unsigned char blue)
{
	try
	{
		if (this->m_textureMap.at(t_fileName) != NULL) {		//check if texture has been added
			throw std::runtime_error(" ERROR: Duplicate texture (ID: " + (std::string)t_fileName + ") loaded. ");
		} 	
	}
	catch (std::out_of_range exc) {		// if not, then add it

		this->m_textureMap[t_fileName] = new Texture(red, green, blue);
		return;
	}
	return;
}

Texture* TextureManager::privGet(const char* t_fileName)
{
	try
	{
		return this->m_textureMap.at(t_fileName);		//return texture, if it is valid
	}
	catch (std::out_of_range exc)		// if not, throw
	{		
		throw std::runtime_error(" ERROR: Texture (ID: " + (std::string) t_fileName + ") not found. ");
	}
}

void TextureManager::privDelete()
{
	std::map<std::string, Texture*>::iterator it;

	for (it = this->m_textureMap.begin(); it != this->m_textureMap.end(); it++)
	{
		delete it->second;
	}

	this->m_textureMap.clear();

	DebugMsg::out(" \n SHADER MANAGER: size: %d ", this->m_textureMap.size());

	delete this->m_ptrInstance;
}
