#ifndef _jsonhandlerattorney
#define _jsonhandlerattorney

class JsonHandlerAttorney
{
	friend class KapEngine;
private:
	static void Delete();

public:
	JsonHandlerAttorney() = delete;
	JsonHandlerAttorney(const JsonHandlerAttorney&) = delete;
	JsonHandlerAttorney operator=(const JsonHandlerAttorney&) = delete;
	~JsonHandlerAttorney() = delete;
};

#endif _jsonhandlerattorney
#pragma once
