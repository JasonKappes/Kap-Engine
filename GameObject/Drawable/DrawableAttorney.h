#ifndef _drawableattorney
#define _drawableattorney

class Drawable;

class DrawableAttorney
{
public:
	class GameLoop
	{
		friend class DrawableManager;
	private:
		static void Draw(Drawable*);
		static void Draw2D(Drawable*);

	private:
		GameLoop() = delete;
		GameLoop(const GameLoop&) = delete;
		GameLoop operator=(const GameLoop&) = delete;
		~GameLoop() = delete;

	};

public:
	class Registration
	{
		friend class DrawRegistrationCommand;
		friend class DrawDeRegistrationCommand;
	private:
		static void SceneRegistration(Drawable*);
		static void SceneDeRegistration(Drawable*);

	private:
		Registration() = delete;
		Registration(const Registration&) = delete;
		Registration operator=(const Registration&) = delete;
		~Registration() = delete;
	};

private:
	DrawableAttorney() = delete;
	DrawableAttorney(const DrawableAttorney&) = delete;
	DrawableAttorney operator=(const DrawableAttorney&) = delete;
	~DrawableAttorney() = delete;
};

#endif _drawableattorney
#pragma once
