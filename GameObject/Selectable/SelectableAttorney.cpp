#include "SelectableAttorney.h"

void SelectableAttorney::Registration::SceneRegistration(Selectable* t_selectable) { t_selectable->SceneSelectionRegistration(); }

void SelectableAttorney::Registration::SceneDeRegistration(Selectable* t_selectable) { t_selectable->SceneSelectionDeRegistration(); }

void SelectableAttorney::Editor::FastSceneRegistration(Selectable* t_selectable) { t_selectable->FastSelectionRegistration(); }

void SelectableAttorney::Editor::FastSceneDeRegistration(Selectable* t_selectable) { t_selectable->FastSelectionDeRegistration(); }

void SelectableAttorney::Editor::SetSelectionModel(Selectable* t_selectable, Selectable::Volume chosenCollisionVolume)
{
	t_selectable->SetSelectionModel(chosenCollisionVolume);
}

