#ifndef _spritefontmanagerattorney
#define _spritefontmanagerattorney

class SpriteFontManagerAttorney
{
	friend class KapEngine;

private:
	static void Delete();

	SpriteFontManagerAttorney() = delete;
	SpriteFontManagerAttorney(const SpriteFontManagerAttorney&) = delete;
	SpriteFontManagerAttorney operator= (const SpriteFontManagerAttorney&) = delete;
	~SpriteFontManagerAttorney() = delete;
};

#endif _spritefontmanagerattorney
#pragma once
