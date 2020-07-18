#ifndef _drawable
#define _drawable
#include "Registration.h"
#include "DrawableManager.h"

class DrawRegistrationCommand;
class DrawDeRegistrationCommand;

class Drawable
{
	friend class DrawableAttorney;

protected: // ---> USER METHODS

	/// <summary>
	/// Called by a GameObject to register itself to be called to Draw() every frame.
	/// </summary> 
	/// \ingroup Drawable
	void SubmitDrawRegistration();

	/// <summary>
	/// Called by a GameObject to de-register itself from being called to Draw().
	/// </summary> 
	/// \ingroup Drawable
	void SubmitDrawDeRegistration();

protected:
	Drawable();
	Drawable(const Drawable&) = delete;
	virtual ~Drawable();

private: // ---> ENGINE CALLBACKS, USER METHODS (to override)

	/// <summary>
	/// Overrided by all GameObjects. This function will be called after a GameObject calls SubmitDrawRegistration(). It is called every frame.
	/// 
	/// Recommended practice inside of this function is to make 3D render calls, to show an object on the screen.
	/// 
	/// Example Syntax: pGraphicsObject->Render(SceneManager::Get3DCamera());
	/// </summary> 
	/// \ingroup Drawable
	virtual void Draw() = 0;

	/// <summary>
	/// Overrided by all GameObjects. This function will be called after a GameObject calls SubmitDrawRegistration().
	/// 
	/// Recommended practice inside of this function is to make 2D render calls; to show a HUD-like image on screen.
	/// 
	/// Example Syntax: pSpriteString->Render();
	/// </summary> 
	/// \ingroup Drawable
	virtual void Draw2D() {};

private: // ----> ENGINE METHODS
	void SceneRegistration();
	void SceneDeRegistration();

private:
	RegistrationState m_registrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	DrawableManager::StorageListRef m_deleteRef;
	DrawRegistrationCommand* m_registrationCommand;
	DrawDeRegistrationCommand* m_deregistrationCommand;
};


#endif _drawable
#pragma once
