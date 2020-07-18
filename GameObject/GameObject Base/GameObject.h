#ifndef _gameobject
#define _gameobject
#include "Updatable.h"
#include "Drawable.h"
#include "Inputable.h"
#include "Alarmable.h"
#include "Collidable.h"
#include "Touchable.h"
#include "KapSprite.h"
#include "SpriteFont.h"
#include "SpriteFontManager.h"
#include "ScreenLog.h"
#include "Serializable.h"
#include "Selectable.h"
#include "Transform.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "TextureManager.h"
#include "ShaderManager.h"
#include "Color.h"
#include "Cursor.h"

class GameObjectEntryCommand;
class GameObjectExitCommand;
class Transform;
class jsonData;


class GameObject : public Updatable, public Drawable, public Alarmable, public Inputable, public Touchable,
	public Collidable, public Serializable, public Selectable, public Align16
{
	friend class GameObjectAttorney;
public:
	virtual ~GameObject();
	GameObject(const GameObject&) = delete;
	GameObject();

	Transform* GetTransform() const;

protected:
	Transform* transform;

protected: // --- > USER METHODS (to override)

	/// <summary>
	/// This method is called the frame after SubmitEntry() is called.
	/// 
	/// Any scene registrations for alarms, collision, draw, update, and input should be done inside this method.
	/// </summary> 
	/// \ingroup GameObjectBase
	virtual void SceneEntry() {};

	/// <summary>
	/// This method is called the frame after SubmitExit() is called.
	/// 
	/// Any systems this GameObject registered for, should be submitted for de-registration inside here.
	/// </summary> 
	/// \ingroup GameObjectBase
	virtual void SceneExit() {};


protected: // --- > ENGINE METHOD, USER METHOD (to be called)
	void SubmitEntry();
	void SubmitExit();

protected:
	RegistrationState m_currState = RegistrationState::PENDING_REGISTRATION;
	GameObjectEntryCommand* m_gameObjectEntryCommand;
	GameObjectExitCommand* m_gameObjectExitCommand;
	Model* m_Plane;

private: // --- > ENGINE METHOD
	void ConnectToScene();
	void DisconnectFromScene();
};

#endif _gameobject
#pragma once
