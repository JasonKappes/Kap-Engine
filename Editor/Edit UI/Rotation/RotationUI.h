#ifndef _rotationui
#define _rotationui
#include "GraphicsObject_WireframeConstantColor.h"
#include "GraphicsObject_TextureFlat.h"
#include "TextureManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "GroupUI.h"

class xRotUI;
class yRotUI;
class zRotUI;

//Manages the rotation indicators
class RotationUI : public GroupUI
{
public:
	RotationUI();
	RotationUI(const RotationUI&) = delete;
	RotationUI operator=(const RotationUI&) = delete;
	~RotationUI();

	//This allows the various rotation indicators to be selected (registers them for selection)
	void EnableIndicator() override;

	//This removes the rotation indicators from being selected (deregisters them for selection)
	void ResetIndicator() override;

	//Tells each rotation indicator to be rendered
	void DrawUI() override;

	//Updates Rotation indicators world information
	void UpdateUI(float radius, const Vect& center) override;

private:
	xRotUI* xindicator;
	yRotUI* yindicator;
	zRotUI* zindicator;
};

#endif _rotation
#pragma once
