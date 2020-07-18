#include "UpdatableAttorney.h"
#include "Updatable.h"
#include "UpdateRegistrationCommand.h"

void UpdatableAttorney::GameLoop::Update(Updatable* t_updatable) { t_updatable->Update(); }

void UpdatableAttorney::GameLoop::LateUpdate(Updatable* t_updatable) { t_updatable->LateUpdate(); }

void UpdatableAttorney::Registration::SceneRegistration(Updatable* t_updatable) { t_updatable->SceneRegistration(); }

void UpdatableAttorney::Registration::SceneDeRegistration(Updatable* t_updatable) { t_updatable->SceneDeRegistration(); }
