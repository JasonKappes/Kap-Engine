#include "GroupUI.h"

GroupUI::GroupUI() : emptyIndicator(new EmptyIndicator()), selectedIndicator(nullptr) {}

GroupUI::~GroupUI() { delete emptyIndicator; }

void GroupUI::SetIndicator(WorldUI* t_selectedIndicator)
{
	this->selectedIndicator = t_selectedIndicator;
}

void GroupUI::EmptyIndicatorSelected()
{
	selectedIndicator = emptyIndicator;
}

WorldUI& GroupUI::GetSelectedIndicator()
{
	return *this->selectedIndicator;
}