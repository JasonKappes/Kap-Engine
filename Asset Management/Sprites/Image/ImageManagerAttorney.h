#ifndef _imagemanagerattorney
#define _imagemanagerattorney

class ImageManagerAttorney
{
	friend class KapEngine;
private:
	static void Delete();

private:
	ImageManagerAttorney() = delete;
	ImageManagerAttorney(const ImageManagerAttorney&) = delete;
	ImageManagerAttorney operator=(const ImageManagerAttorney&) = delete;
	~ImageManagerAttorney() = delete;
};

#endif _imagemanagerattorney
#pragma once
