#include "DrawRegistrationCommand.h"
#include "DrawableAttorney.h"

DrawRegistrationCommand::DrawRegistrationCommand(Drawable* t_drawable) : m_ptrDrawable(t_drawable) {}

void DrawRegistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneRegistration(this->m_ptrDrawable);
}
