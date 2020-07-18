#include "RotationUI.h"
#include "SceneManager.h"
#include "Color.h"
#include "KapMathTools.h"
#include "xRotUI.h"
#include "yRotUI.h"
#include "zRotUI.h"

RotationUI::RotationUI()
{
	xindicator = new xRotUI(this);
	yindicator = new yRotUI(this);
	zindicator = new zRotUI(this);

	this->selectedIndicator = this->emptyIndicator;
}

RotationUI::~RotationUI()
{
	delete xindicator;
	delete yindicator;
	delete zindicator;
}

void RotationUI::ResetIndicator()
{
	xindicator->RemoveSelectable();
	yindicator->RemoveSelectable();
	zindicator->RemoveSelectable();
}

void RotationUI::EnableIndicator()
{
	xindicator->AddSelectable();
	yindicator->AddSelectable();
	zindicator->AddSelectable();
}

void RotationUI::DrawUI()
{
	xindicator->DrawIndicator();
	yindicator->DrawIndicator();
	zindicator->DrawIndicator();
}

void RotationUI::UpdateUI(float radius, const Vect& center)
{
	xindicator->Display(radius, center);
	yindicator->Display(radius, center);
	zindicator->Display(radius, center);
}