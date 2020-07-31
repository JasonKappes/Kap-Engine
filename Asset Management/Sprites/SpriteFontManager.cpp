#include "SpriteFontManager.h"
#include "TextureManager.h"
#include "SpriteFont.h"
#include <DebugOut.h>

SpriteFontManager* SpriteFontManager::m_ptrInstance = nullptr;

std::string SpriteFontManager::defaultKeyAsset = "Fonts/Dosis2";

void SpriteFontManager::privLoad(const char* t_chosenName, const char* t_filename)
{
	try
	{
		if (this->m_fontMap.at(t_filename) != NULL) {			//check if sprite font has been added
			throw std::runtime_error(" ERROR: Duplicate sprite font (ID: " + (std::string)t_filename + ") loaded. ");
		}
	}
	catch (std::out_of_range exc) {		// if not, then add it		
		SpriteFont* f = new SpriteFont(t_filename);
		this->m_fontMap.insert({ t_chosenName,f });
	}
}

SpriteFont* SpriteFontManager::privGet(const char* t_chosenName)
{
	try
	{
		return this->m_fontMap.find(t_chosenName)->second;			//return model, if it is valid
	}
	catch (std::out_of_range exc)							// if not, throw
	{
		throw std::runtime_error(" ERROR: Model (ID: " + (std::string) t_chosenName + ") not found. ");
	}
}

void SpriteFontManager::privDelete()
{
	std::map<std::string, SpriteFont*>::iterator it;

	for (it = this->m_fontMap.begin(); it != this->m_fontMap.end(); it++)
	{
		delete it->second;
	}

	this->m_fontMap.clear();

	delete this->m_ptrInstance;
}
