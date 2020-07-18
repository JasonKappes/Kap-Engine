#include "WorldUI.h"

WorldUI::WorldUI() : transform(new Transform()), displayRadiusDistance(0.0f), startingScale(1.0f), rescaleFactor(1.0f), rescaleRateDividend(1.0f), radiusSpread(1.0f) {};

WorldUI::~WorldUI() { delete transform; }

void WorldUI::DrawIndicator()
{
	transform->Render();
}

void WorldUI::AddSelectable() { SelectableAttorney::Editor::FastSceneRegistration(this); }

void WorldUI::RemoveSelectable() { SelectableAttorney::Editor::FastSceneDeRegistration(this); }
