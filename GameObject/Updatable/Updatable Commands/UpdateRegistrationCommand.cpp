#include "UpdateRegistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateRegistrationCommand::UpdateRegistrationCommand(Updatable* t_updatable) : m_ptrUpdatable(t_updatable) {}

void UpdateRegistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneRegistration(this->m_ptrUpdatable);
}
