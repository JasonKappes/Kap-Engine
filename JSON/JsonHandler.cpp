#include "JsonHandler.h"
#include "json.h"
#include "GameObject.h"
#include <fstream>
#include <iostream>
#include "PlayerTank.h"
#include "Bullet.h"
#include <iterator>
#pragma warning( disable : 4244 )

JsonHandler* JsonHandler::m_ptrInstance = nullptr;

void JsonHandler::EmptyWrite()
{
	std::ofstream file(Instance().currSceneFilePath);
	file << Instance().myFile << std::endl;
}

JsonHandler::JsonHandler() : myFile(*new json()), filePackage(nullptr) {}

JsonHandler::~JsonHandler() 
{  
	DataIt it = this->dataColl.begin();
	while (it != this->dataColl.end())
	{
		this->dataColl.erase(it++);
	}
	
	delete &myFile;
}

void JsonHandler::privLoadData(std::string scenename)
{
	//parameter passed in is "class name"... cut out the "class" part to just have the name
	scenename = scenename.substr(6, scenename.length());

	this->currSceneFilePath = "SerializedData/" + scenename + ".json";
	this->LogFilePath = "";
	std::string key;

	if (does_file_exist(this->currSceneFilePath)) //if the file path exists
	{	
		std::string fileInd = "1";
		this->LogFilePath = "SerializedData/log" + fileInd + scenename + ".json";
		while (does_file_exist(this->LogFilePath))
		{
			fileInd = std::to_string(std::stoi(fileInd) + 1);
			this->LogFilePath = "SerializedData/log" + fileInd + scenename + ".json";
		}
		std::ifstream ifs(currSceneFilePath);

		json j = json::parse(ifs);
		for (json& val : j)
		{
			jsonData* package = prepPackage(val);
			key = package->GetUserType();
			this->dataColl.insert({ key, package });
		}
	}
}

void JsonHandler::privGetWaitingPackage(Serializable* t_serializable)
{
	//reconstruct obj w this data
	SerializableAttorney::Data::DeSerialize(t_serializable, filePackage);
	//t_serializable->DeSerialize(filePackage);

	//delete package
	delete filePackage;

	filePackage = nullptr;
}

void JsonHandler::privDeSerialize(Serializable* t_serializable)
{
	//get data for some object of this type (doesn't matter the obj)
	std::string objectType = t_serializable->GetTypeName();
	DataIt it = dataColl.find(objectType);

	if (it != dataColl.end())
	{
		jsonData* package = it->second;

		//reconstruct obj w this data
		SerializableAttorney::Data::DeSerialize(t_serializable, package);

		//delete package
		delete it->second;

		//obj deserialized, remove package
		dataColl.erase(it);
	}
}

void JsonHandler::privSerialize(jsonData* t_data)
{
	//Type Name + the type count
	std::string type	= t_data->GetUserType();
	std::string objname = type + std::to_string(t_data->GetInstanceID());

	//data
	myFile[objname]["type"]			=   t_data->GetUserType();
	myFile[objname]["position:x"]	=	t_data->GetPosition().X();
	myFile[objname]["position:y"]	=	t_data->GetPosition().Y();
	myFile[objname]["position:z"]	=	t_data->GetPosition().Z();
	myFile[objname]["position:w"]	=	t_data->GetPosition().W();

	Matrix rotation = t_data->GetRotation();
	myFile[objname]["rotation:x1"]	= rotation.get(ROW_0).X();
	myFile[objname]["rotation:y1"]	= rotation.get(ROW_0).Y();
	myFile[objname]["rotation:z1"]	= rotation.get(ROW_0).Z();
	myFile[objname]["rotation:w1"]	= rotation.get(ROW_0).W();

	myFile[objname]["rotation:x2"]	= rotation.get(ROW_1).X();
	myFile[objname]["rotation:y2"]	= rotation.get(ROW_1).Y();
	myFile[objname]["rotation:z2"]	= rotation.get(ROW_1).Z();
	myFile[objname]["rotation:w2"]	= rotation.get(ROW_1).W();

	myFile[objname]["rotation:x3"]	= rotation.get(ROW_2).X();
	myFile[objname]["rotation:y3"]	= rotation.get(ROW_2).Y();
	myFile[objname]["rotation:z3"]	= rotation.get(ROW_2).Z();
	myFile[objname]["rotation:w3"]	= rotation.get(ROW_2).W();

	myFile[objname]["rotation:x4"]	= rotation.get(ROW_3).X();
	myFile[objname]["rotation:y4"]	= rotation.get(ROW_3).Y();
	myFile[objname]["rotation:z4"]	= rotation.get(ROW_3).Z();
	myFile[objname]["rotation:w4"]	= rotation.get(ROW_3).W();

	Matrix& scale = t_data->GetScale();
	myFile[objname]["scale:x1"]		= scale.get(ROW_0).X();
	myFile[objname]["scale:y1"]		= scale.get(ROW_0).Y();
	myFile[objname]["scale:z1"]		= scale.get(ROW_0).Z();
	myFile[objname]["scale:w1"]		= scale.get(ROW_0).W();

	myFile[objname]["scale:x2"]		= scale.get(ROW_1).X();
	myFile[objname]["scale:y2"]		= scale.get(ROW_1).Y();
	myFile[objname]["scale:z2"]		= scale.get(ROW_1).Z();
	myFile[objname]["scale:w2"]		= scale.get(ROW_1).W();

	myFile[objname]["scale:x3"]		= scale.get(ROW_2).X();
	myFile[objname]["scale:y3"]		= scale.get(ROW_2).Y();
	myFile[objname]["scale:z3"]		= scale.get(ROW_2).Z();
	myFile[objname]["scale:w3"]		= scale.get(ROW_2).W();

	myFile[objname]["scale:x4"]		= scale.get(ROW_3).X();
	myFile[objname]["scale:y4"]		= scale.get(ROW_3).Y();
	myFile[objname]["scale:z4"]		= scale.get(ROW_3).Z();
	myFile[objname]["scale:w4"]		= scale.get(ROW_3).W();
	

	std::ofstream file(this->currSceneFilePath);
	file << myFile << std::endl;
}

void JsonHandler::CreateBackupSave()
{
	if (Instance().LogFilePath != "")
	{
		ifstream infile(Instance().currSceneFilePath);
		ofstream outfile(Instance().LogFilePath);
		string content = "";
		int i;

		for (i = 0; infile.eof() != true; i++) // get content of infile
			content += infile.get();

		i--;
		content.erase(content.end() - 1);     // erase last character

		cout << i << " characters read...\n";
		infile.close();

		outfile << content;                 // output
		outfile.close();
	}
}

jsonData* JsonHandler::prepPackage(json& val)
{
	float p_x, p_y, p_z, p_w; //position
	float r_x1, r_y1, r_z1, r_w1, r_x2, r_y2, r_z2, r_w2, r_x3, r_y3, r_z3, r_w3, r_x4, r_y4, r_z4, r_w4; //rotation

	std::string type;
	jsonData* package = new jsonData();

	//get object type + transform data
	val.at("type").get_to(type);
	val.at("position:x").get_to(p_x);
	val.at("position:y").get_to(p_y);
	val.at("position:z").get_to(p_z);
	val.at("position:w").get_to(p_w);

	package->SetPosition(Vect(p_x, p_y, p_z, p_w));

	val.at("rotation:x1").get_to(r_x1);
	val.at("rotation:y1").get_to(r_y1);
	val.at("rotation:z1").get_to(r_z1);
	val.at("rotation:w1").get_to(r_w1);

	val.at("rotation:x2").get_to(r_x2);
	val.at("rotation:y2").get_to(r_y2);
	val.at("rotation:z2").get_to(r_z2);
	val.at("rotation:w2").get_to(r_w2);

	val.at("rotation:x3").get_to(r_x3);
	val.at("rotation:y3").get_to(r_y3);
	val.at("rotation:z3").get_to(r_z3);
	val.at("rotation:w3").get_to(r_w3);

	val.at("rotation:x4").get_to(r_x4);
	val.at("rotation:y4").get_to(r_y4);
	val.at("rotation:z4").get_to(r_z4);
	val.at("rotation:w4").get_to(r_w4);

	package->SetRotation(Matrix(Vect(r_x1, r_y1, r_z1, r_w1),
		Vect(r_x2, r_y2, r_z2, r_w2),
		Vect(r_x3, r_y3, r_z3, r_w3),
		Vect(r_x4, r_y4, r_z4, r_w4)));

	val.at("scale:x1").get_to(r_x1);
	val.at("scale:y1").get_to(r_y1);
	val.at("scale:z1").get_to(r_z1);
	val.at("scale:w1").get_to(r_w1);

	val.at("scale:x2").get_to(r_x2);
	val.at("scale:y2").get_to(r_y2);
	val.at("scale:z2").get_to(r_z2);
	val.at("scale:w2").get_to(r_w2);

	val.at("scale:x3").get_to(r_x3);
	val.at("scale:y3").get_to(r_y3);
	val.at("scale:z3").get_to(r_z3);
	val.at("scale:w3").get_to(r_w3);

	val.at("scale:x4").get_to(r_x4);
	val.at("scale:y4").get_to(r_y4);
	val.at("scale:z4").get_to(r_z4);
	val.at("scale:w4").get_to(r_w4);

	package->SetScale(Matrix(Vect(r_x1, r_y1, r_z1, r_w1), 
		Vect(r_x2, r_y2, r_z2, r_w2), 
		Vect(r_x3, r_y3, r_z3, r_w3), 
		Vect(r_x4, r_y4, r_z4, r_w4)));

	package->SetUserType(type);

	return package;
}

void JsonHandler::Delete()
{
	delete JsonHandler::m_ptrInstance;
}
