#ifndef _screenlogattorney
#define _screenlogattorney

class ScreenLogAttorney
{
	friend class KapEngine;
private:
	static void Delete();
	static void Render();

private:
	ScreenLogAttorney() = delete;
	ScreenLogAttorney(const ScreenLogAttorney&) = delete;
	ScreenLogAttorney operator=(const ScreenLogAttorney&) = delete;
	~ScreenLogAttorney() = delete;
};

#endif _screenlogattorney
#pragma once
