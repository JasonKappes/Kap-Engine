#ifndef _gamedraw
#define _gamedraw
#include "SystemUpdate.h"
#include "DrawableManager.h"

//If EDITOR MODE is disabled, this is the draw mode chosen
class GameDraw : public SystemUpdate
{
public:
	GameDraw() = default;
	GameDraw(const GameDraw&) = delete;
	~GameDraw() = default;

	GameDraw(const DrawableManager& d) { drawableManager = &d; }

	void Tick() const override { drawableManager->ProcessElements(); }

private:
	const DrawableManager* drawableManager;
};

#endif _gamedraw
#pragma once
