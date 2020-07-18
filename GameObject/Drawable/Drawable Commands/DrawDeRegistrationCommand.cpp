#include "DrawDeRegistrationCommand.h"
#include "DrawableAttorney.h"

DrawDeRegistrationCommand::DrawDeRegistrationCommand(Drawable* t_drawable) : m_ptrDrawable(t_drawable) {}

void DrawDeRegistrationCommand::Execute()
{
	DrawableAttorney::Registration::SceneDeRegistration(this->m_ptrDrawable);
}
