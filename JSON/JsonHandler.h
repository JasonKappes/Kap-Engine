#ifndef _jsonhandler
#define _jsonhandler
#include "DebugOut.h"
#include "jsonData.h"
#include <map>

class Transform;
class GameObject;
class JsonData;
class Serializable;

class JsonHandler
{
	friend class JsonHandlerAttorney;
public:
	using UserType = std::string;
	using JsonDataColl = std::multimap<std::string, jsonData*>;
	using DataIt = JsonDataColl::iterator;	

public:
	template <typename scene>
	static void LoadData()									{ Instance().privLoadData(std::string(typeid(scene).name()));			}
	static void EmptyWrite();
	static void CreateBackupSave();

	template <typename type>
	static void LoadFileObjects()
	{
		std::string type_name = typeid(type).name();
		DataIt it = Instance().dataColl.find(type_name + "0");
		if (it != Instance().dataColl.end())
		{
			Instance().filePackage = it->second; //save package for this object
			Instance().dataColl.erase(it);
			new type();			  //create this object since it lives on file
		}
	}

	static bool WaitingData() {
		return Instance().privWaitingData();
	}
	
	static void GetWaitingPackage(Serializable* s) { Instance().privGetWaitingPackage(s); }

	static void DeSerialize(Serializable* s)				{ Instance().privDeSerialize(s);			}
	static void Serialize(jsonData* data)					{ Instance().privSerialize(data);			}

private:
	JsonHandler();
	JsonHandler(const JsonHandler&) = delete;
	JsonHandler operator=(const JsonHandler&) = delete;
	~JsonHandler();

	static JsonHandler& Instance()
	{
		if (!m_ptrInstance)
			m_ptrInstance = new JsonHandler();
		return *m_ptrInstance;
	}

	static void Delete();

	void privDeSerialize(Serializable*);
	void privSerialize(jsonData*);
	bool privWaitingData() { return this->filePackage != nullptr; }

	void privLoadData(std::string scenename);
	void privGetWaitingPackage(Serializable* s);

	void createBackupFile(const std::string& scenename);

	jsonData* prepPackage(json& key);

	//source: https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exist-using-standard-c-c11-c
	inline bool does_file_exist(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

private:
	static JsonHandler* m_ptrInstance;
	std::string currSceneFilePath;
	std::string LogFilePath;
	JsonDataColl dataColl;
	jsonData* filePackage;
	json& myFile;
};

#endif _jsonhandler
#pragma once
