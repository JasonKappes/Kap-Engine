#ifndef _modelmanagerattorney
#define _modelmanagerattorney

class ModelManagerAttorney
{
	friend class KapEngine;

private:
	static void Delete();

private:
	ModelManagerAttorney() = delete;
	ModelManagerAttorney(const ModelManagerAttorney&) = delete;
	ModelManagerAttorney operator=(const ModelManagerAttorney&) = delete;
	~ModelManagerAttorney() = delete;
};

#endif _modelmanagerattorney
#pragma once
