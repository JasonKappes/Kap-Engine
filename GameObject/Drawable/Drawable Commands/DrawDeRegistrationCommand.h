#ifndef _drawderegistrationcommand
#define _drawderegistrationcommand
#include "SceneRegistrationCommand.h"

class Drawable;

class DrawDeRegistrationCommand : public SceneRegistrationCommand
{
public:
	DrawDeRegistrationCommand() = delete;
	DrawDeRegistrationCommand(Drawable* t_updatable);
	DrawDeRegistrationCommand(const DrawDeRegistrationCommand&) = delete;
	DrawDeRegistrationCommand operator=(const DrawDeRegistrationCommand&) = delete;

protected:
	void Execute() override;

private:
	Drawable* m_ptrDrawable;
};

#endif _drawderegistrationcommand
#pragma once
