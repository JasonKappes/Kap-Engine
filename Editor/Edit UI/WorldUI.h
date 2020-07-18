#ifndef _worldui
#define _worldui
#include "Drawable.h"
#include "GraphicsObject_TextureFlat.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Raycast.h"
#include "Serializable.h"
#include "RollbackHandlerAttorney.h"
#include "SelectableAttorney.h"

class WorldUI : public Selectable
{
public:
	WorldUI();
	WorldUI(const WorldUI&) = delete;
	virtual ~WorldUI();

	virtual void Display(float radius, const Vect & center) = 0;

	virtual void ForwardMovement(Serializable*) {}

	virtual void BackwardMovement(Serializable*) {}

	virtual void LeftMovement(Serializable*) {}

	virtual void RightMovement(Serializable*) {}

	virtual void DrawIndicator();

	void AddSelectable();

	void RemoveSelectable();

protected:
	Transform* transform;

	float displayRadiusDistance;

	float startingScale;

	float rescaleFactor;

	float rescaleRateDividend;

	float radiusSpread;
};

#endif _worldui
#pragma once
