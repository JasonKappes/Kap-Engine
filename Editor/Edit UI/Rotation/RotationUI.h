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

class RotationUI : public GroupUI
{
public:
	RotationUI();
	RotationUI(const RotationUI&) = delete;
	RotationUI operator=(const RotationUI&) = delete;
	~RotationUI();

	void EnableIndicator() override;

	void ResetIndicator() override;

	void DrawUI() override;

	void UpdateUI(float radius, const Vect& center) override;

private:
	xRotUI* xindicator;
	yRotUI* yindicator;
	zRotUI* zindicator;
};

#endif _rotation
#pragma once
