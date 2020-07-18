#include "SelectionDeRegistrationCommand.h"
#include "SelectableAttorney.h"

SelectionDeRegistrationCommand::SelectionDeRegistrationCommand(Selectable* t_selectable) : m_ptrSelectable(t_selectable) {}

void SelectionDeRegistrationCommand::Execute()
{
	SelectableAttorney::Registration::SceneDeRegistration(this->m_ptrSelectable);
}
