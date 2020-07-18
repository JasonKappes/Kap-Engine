#ifndef _updatable
#define _updatable
#include "Registration.h"
#include "UpdatableManager.h"

class UpdateRegistrationCommand;
class UpdateDeRegistrationCommand;

class Updatable
{
	friend class UpdatableAttorney;

protected: // --- > USER METHODS
	/// <summary>
	/// Register a GameObject to register itself to be called to Update() every frame.
	/// </summary> 
	/// \ingroup Updatable
	void SubmitUpdateRegistration();

	/// <summary>
	/// Register a GameObject to de-register itself to be called to Update() every frame.
	/// </summary> 
	/// \ingroup Updatable
	void SubmitUpdateDeRegistration();


protected:
	virtual ~Updatable();
	Updatable();
	Updatable(const Updatable&) = delete;

private: // --- > ENGINE CALLBACKS, USER METHODS (to override)

	/// <summary>
	/// Overrided by all GameObjects. This function will be called after a GameObject calls SubmitUpdateRegistration(). It is called every frame.
	/// 
	/// Recommended practice inside of this function is to make per-frame calculations.
	/// 
	/// </summary> 
	/// \ingroup Updatable
	virtual void Update() {};

	virtual void LateUpdate() {};

private: // ---> ENGINE METHODS
	void SceneRegistration();
	void SceneDeRegistration();

protected:
	RegistrationState m_updatableRegistrationState = RegistrationState::CURRENTLY_DEREGISTERED;
	UpdatableManager::StorageListRef m_deleteReference;
	UpdateRegistrationCommand* m_registrationCommand;
	UpdateDeRegistrationCommand* m_deregistrationCommand;
};


#endif _updatable
#pragma once
