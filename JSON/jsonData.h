#ifndef _jsondata
#define _jsondata
#include "json.h"
#include "Matrix.h"

using nlohmann::json;

class jsonData
{
public:
	using UserType = std::string;

public:
	jsonData();
	jsonData(const jsonData&);
	jsonData operator=(const jsonData&) = delete;
	~jsonData() = default;

	jsonData(Vect& pos, Matrix& rot, Matrix& scale, UserType, int);

	Vect& GetPosition();
	void SetPosition(Vect);

	Matrix& GetRotation();
	void SetRotation(Matrix);

	Matrix& GetScale();
	void SetScale(Matrix);

	UserType GetUserType();
	void SetUserType(UserType);

	int GetInstanceID();
	void SetInstanceID(int);

private:
	Vect position;
	Matrix rotation;
	Matrix scale;

	UserType type;
	int typeInstanceID;
};

#endif _jsondata
#pragma once
