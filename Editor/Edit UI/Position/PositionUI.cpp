#include "PositionUI.h"
#include "SceneManager.h"
#include "Color.h"
#include "KapMathTools.h"
#include "ModelManager.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "xPosUI.h"
#include "zPosUI.h"
#include "yPosUI.h"

PositionUI::PositionUI()
{
	this->xindicator= new xPosUI(this);
	this->zindicator = new zPosUI(this);
	this->yindicator = new yPosUI(this);

	this->selectedIndicator = this->emptyIndicator;
}

PositionUI::~PositionUI()
{
	delete xindicator;
	delete zindicator;
	delete yindicator;
}

void PositionUI::EnableIndicator()
{
	xindicator->AddSelectable();
	yindicator->AddSelectable();
	zindicator->AddSelectable();
}

void PositionUI::ResetIndicator()
{
	xindicator->RemoveSelectable();
	yindicator->RemoveSelectable();
	zindicator->RemoveSelectable();
}

void PositionUI::UpdateUI(float radius, const Vect& center)
{
	xindicator->Display(radius, center);
	zindicator->Display(radius, center);
	yindicator->Display(radius, center);
}

void PositionUI::DrawUI()
{
	xindicator->DrawIndicator();
	zindicator->DrawIndicator();
	yindicator->DrawIndicator();
}
