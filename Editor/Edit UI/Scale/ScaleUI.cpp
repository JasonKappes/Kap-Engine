#include "ScaleUI.h"
#include "xyzScaleUI.h"

ScaleUI::ScaleUI()
{
	scaleIndicator = new xyzScaleUI(this);

	this->selectedIndicator = this->emptyIndicator;
}

ScaleUI::~ScaleUI()
{
	delete scaleIndicator;
}

void ScaleUI::EnableIndicator()
{
	scaleIndicator->AddSelectable();
}

void ScaleUI::ResetIndicator()
{
	scaleIndicator->RemoveSelectable();
}

void ScaleUI::UpdateUI(float radius, const Vect& center)
{
	scaleIndicator->Display(radius, center);
}

void ScaleUI::DrawUI()
{
	scaleIndicator->DrawIndicator();
}
