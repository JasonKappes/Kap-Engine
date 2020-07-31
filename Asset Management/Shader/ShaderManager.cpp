#include "ShaderManager.h"
#include "ShaderObject.h"

ShaderManager* ShaderManager::m_ptrInstance = nullptr;

std::string ShaderManager::defaultKeyAsset = "DefaultAssets/textureFlatRender";

//Loads a shader from a given filename
void ShaderManager::privLoad(const char* t_fileName)
{
	try
	{
		if (this->m_shaderMap.at(t_fileName) != NULL) {			//check if shader has been added
			throw std::runtime_error(" ERROR: Duplicate shader (ID: " + (std::string)t_fileName + ") loaded. ");
		}
	}
	catch (std::out_of_range exc) {						// if not, then add it		
		this->m_shaderMap[t_fileName] = new ShaderObject(t_fileName);
	}
}

//Retrieves a shader from a given filename
ShaderObject* ShaderManager::privGet(const char* t_fileName)
{
	try
	{
		return this->m_shaderMap.at(t_fileName);	//return shader, if it is valid
	}
	catch (std::out_of_range exc) 
	{							// if not, throw
		throw std::runtime_error(" ERROR: Shader (ID: " + (std::string) t_fileName + ") not found. ");
	}
}

void ShaderManager::privDelete()
{
	std::map<std::string, ShaderObject*>::iterator it;

	for (it = this->m_shaderMap.begin(); it != this->m_shaderMap.end(); it++)
	{
		delete it->second;
	}

	this->m_shaderMap.clear();

	DebugMsg::out(" \n SHADER MANAGER: size: %d ", this->m_shaderMap.size());
	delete this->m_ptrInstance;
}

