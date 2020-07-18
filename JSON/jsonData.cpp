#include "jsonData.h"
#include "Transform.h"

jsonData::jsonData() : position(Vect()), rotation(Matrix()), scale(Matrix()), type(std::string()), typeInstanceID(1) {}

jsonData::jsonData(const jsonData& t_copy)
{
	this->typeInstanceID	= t_copy.typeInstanceID;
	this->position			= t_copy.position;
	this->rotation			= t_copy.rotation;
	this->scale				= t_copy.scale;
	this->type				= std::string(t_copy.type);
}

jsonData::jsonData(Vect& pos, Matrix& rot, Matrix& sc, UserType t_type, int t_instanceID)
	: position(pos), rotation(rot), scale(sc), type(t_type), typeInstanceID(t_instanceID)
{}

Vect& jsonData::GetPosition()
{
	return this->position;
}

void jsonData::SetPosition(Vect pos)
{
	this->position = pos;
}

void jsonData::SetRotation(Matrix rot)
{
	this->rotation = rot;
}

void jsonData::SetScale(Matrix sc)
{
	this->scale = sc;
}

Matrix& jsonData::GetRotation()
{
	return this->rotation;
}

Matrix& jsonData::GetScale()
{
	return this->scale;
}

jsonData::UserType jsonData::GetUserType()
{
	return type;
}

void jsonData::SetUserType(UserType t_type)
{
	this->type = t_type;
}

int jsonData::GetInstanceID()
{
	return this->typeInstanceID;
}

void jsonData::SetInstanceID(int t_id)
{
	this->typeInstanceID = t_id;
}
