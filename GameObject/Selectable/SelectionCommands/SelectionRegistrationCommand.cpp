#include "SelectionRegistrationCommand.h"
#include "SelectableAttorney.h"

SelectionRegistrationCommand::SelectionRegistrationCommand(Selectable* t_selectable) : m_ptrSelectable(t_selectable) {}

void SelectionRegistrationCommand::Execute()
{
	SelectableAttorney::Registration::SceneRegistration(this->m_ptrSelectable);
}
