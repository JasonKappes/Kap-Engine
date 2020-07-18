#ifndef _texturemanagerattorney
#define _texturemanagersattorney

class TextureManagerAttorney
{
	friend class KapEngine;

private:
	static void Delete();

private:
	TextureManagerAttorney() = delete;
	TextureManagerAttorney(const TextureManagerAttorney&) = delete;
	TextureManagerAttorney operator=(const TextureManagerAttorney&) = delete;
	~TextureManagerAttorney() = delete;
};

#endif _texturemanagerattorney
#pragma once
