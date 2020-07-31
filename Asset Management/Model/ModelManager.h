#ifndef _modelmanager
#define _modelmanager
#include "Model.h"

//Singleton class --> Can be accessed to Retrieve and Load models by the user
class ModelManager
{
	friend class ModelManagerAttorney;
public: /// ----> USER METHODS

	/// Loads a model for use by a GameObject.
	/// Takes a user-defined path to the model as input. To be called from LoadAllResources.cpp
	static void Load(const char* t_fileName) { Instance().privLoad(t_fileName); }

	/// Called from a GameObject to retrieve a loaded model
	static Model* Get(const char* t_fileName) { return Instance().privGet(t_fileName); }

	/// Loads a premade model for use by a GameObject.
	/// Takes a preMadeModel (from the Model class) as input. To be called from LoadAllResources.cpp
	static void Load(Model::PreMadeModels t_premademodel) { Instance().privLoad(t_premademodel); }

	/// Called from a GameObject to retrieve a loaded model
	static Model* Get(Model::PreMadeModels t_premademodel) { return Instance().privGet(t_premademodel); }

public:
	
	static std::string defaultAssetKey;

private:
	ModelManager() = default;
	ModelManager(const ModelManager&) = delete;
	ModelManager operator=(const ModelManager&) = delete;
	~ModelManager() = default;

	static ModelManager& Instance()	    // Access reference (all public methods will be static)
	{
		if (!m_ptrInstance)
			m_ptrInstance = new ModelManager;
		return *m_ptrInstance;
	};

	static void Delete() { Instance().privDelete(); }

	void privDelete();
	void privLoad(const char* t_fileName);
	void privLoad(Model::PreMadeModels t_premademodel);
	Model* privGet(const char* t_fileName);
	Model* privGet(Model::PreMadeModels t_premademodel);
	std::string privKeyConversion(Model::PreMadeModels t_premademodel);

private: 
	static ModelManager* m_ptrInstance;
	typedef std::map<std::string, Model*> modelMap;
	modelMap m_modelMap;
};


#endif _modelmanager
#pragma once
