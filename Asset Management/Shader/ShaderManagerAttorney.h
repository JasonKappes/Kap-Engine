#ifndef _shadermanagerattorney
#define _shadermanagerattorney

class ShaderManagerAttorney
{
	friend class KapEngine;

private:
	static void Delete();

private:
	ShaderManagerAttorney() = delete;
	ShaderManagerAttorney(const ShaderManagerAttorney&) = delete;
	ShaderManagerAttorney operator=(const ShaderManagerAttorney&) = delete;
	~ShaderManagerAttorney() = delete;
};

#endif _shadermanagerattorney
#pragma once
