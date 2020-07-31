#include "ModelManager.h"

ModelManager* ModelManager::m_ptrInstance = nullptr;

std::string ModelManager::defaultAssetKey = "DefaultAssets/space_frigate.azul";

//Loads a model from a filename
void ModelManager::privLoad(const char* t_fileName)
{
	try
	{
		if (this->m_modelMap.at(t_fileName) != NULL) {
			throw std::runtime_error(" ERROR: Duplicate model (ID: " + (std::string)t_fileName + ") loaded. ");
		} 
	}
	catch (std::out_of_range exc) {

		this->m_modelMap[t_fileName] = new Model(t_fileName);
		return;
	}
	return;
}

//Loads a premade model
void ModelManager::privLoad(Model::PreMadeModels t_premademodel)
{
	std::string key = privKeyConversion(t_premademodel);
	try
	{
;		if (this->m_modelMap.at(key) != NULL) {		//Check if Model has been added
			throw std::runtime_error(" ERROR: Duplicate model (ID: " + (std::string)key + ") loaded. ");
		}
	}
	catch (std::out_of_range exc) {		// if not, then add it

		this->m_modelMap[key] = new Model(t_premademodel);
		return;
	}
	return;
}

//Retrieves a model (If it has been loaded) with a given filename 
Model* ModelManager::privGet(const char* t_fileName)
{
	try
	{
		return this->m_modelMap.at(t_fileName);			// return model, if it is valid
	}
	catch (std::out_of_range exc)					// if not, throw
	{		
		throw std::runtime_error(" ERROR: Model (ID: " + (std::string) t_fileName + ") not found. ");
	}	
}

//Retrieves a premade model (If it has been loaded)
Model* ModelManager::privGet(Model::PreMadeModels t_premademodel)
{
	std::string key = privKeyConversion(t_premademodel);
	try
	{
		return this->m_modelMap.at(key);		// return model, if it is valid
	}
	catch (std::out_of_range exc)				// if not, throw
	{		
		throw std::runtime_error(" ERROR: Model (ID: " + key + ") not found. ");
	}
}

std::string ModelManager::privKeyConversion(Model::PreMadeModels t_premademodel)
{
	switch (t_premademodel)
	{
	case Model::PreMadeModels::UnitSphere:
		return "UnitSphere";
		break;
	case Model::PreMadeModels::UnitBox_WF:
		return "UnitBox";
		break;
	case Model::PreMadeModels::UnitSquareXY:
		return "UnitSquare";
		break;
	default:
		throw std::runtime_error(" ERROR: Premade Model not found. ");
		break;
	}	
}

void ModelManager::privDelete()
{
	std::map<std::string, Model*>::iterator it;

	for (it = this->m_modelMap.begin(); it != this->m_modelMap.end(); ++it)
	{
		delete it->second;
	}

	this->m_modelMap.clear();

	delete this->m_ptrInstance;
}




