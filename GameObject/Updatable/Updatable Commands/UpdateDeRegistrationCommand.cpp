#include "UpdateDeRegistrationCommand.h"
#include "UpdatableAttorney.h"

UpdateDeRegistrationCommand::UpdateDeRegistrationCommand(Updatable* t_updatable) : m_ptrUpdatable(t_updatable) {}

void UpdateDeRegistrationCommand::Execute()
{
	UpdatableAttorney::Registration::SceneDeRegistration(this->m_ptrUpdatable);
}
