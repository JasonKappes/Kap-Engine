#include "DrawableAttorney.h"
#include "Drawable.h"

void DrawableAttorney::GameLoop::Draw(Drawable* t_drawable) { t_drawable->Draw(); }

void DrawableAttorney::GameLoop::Draw2D(Drawable* t_drawable) { t_drawable->Draw2D(); }

void DrawableAttorney::Registration::SceneRegistration(Drawable* t_drawable) { t_drawable->SceneRegistration(); }

void DrawableAttorney::Registration::SceneDeRegistration(Drawable* t_drawable) { t_drawable->SceneDeRegistration(); }
