#ifndef _drawregistrationcommand
#define _drawregistrationcommand
#include "SceneRegistrationCommand.h"

class Drawable;

class DrawRegistrationCommand : public SceneRegistrationCommand
{
public:
	DrawRegistrationCommand() = delete;
	DrawRegistrationCommand(Drawable* t_updatable);
	DrawRegistrationCommand(const DrawRegistrationCommand&) = delete;
	DrawRegistrationCommand operator=(const DrawRegistrationCommand&) = delete;

protected:
	void Execute() override;

private:
	Drawable* m_ptrDrawable;
};

#endif _drawregistrationcommand
#pragma once
