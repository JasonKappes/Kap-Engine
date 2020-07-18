#include "zPosUI.h"
#include "PositionUI.h"
#include "SceneManager.h"
#include "KapMathTools.h"
#include "OldRotationCommand.h"

zPosUI::~zPosUI()
{
	delete this->transform->object;
}

zPosUI::zPosUI(PositionUI* parent)
{
	this->selectable_transform = transform;

	posUIcoll = parent;

	transform->object = new GraphicsObject_TextureFlat(ModelManager::Get("position_ui.azul"), ShaderManager::Get("textureFlatRender"), TextureManager::Get("blue.tga"));

	startingScale = 60.0f;
	rescaleRateDividend = 1500.0f;
	radiusSpread = 0.5f;

	transform->scale = Matrix(SCALE, startingScale, startingScale, startingScale);
	transform->rotation = Matrix(RotType::ROT_X, -1.64f);
	transform->UpdateWorld();

	SelectableAttorney::Editor::SetSelectionModel(this, Selectable::Volume::BSPHERE);
	//SelectableAttorney::Editor::FastSceneRegistration(this);
}

void zPosUI::Display(float radius, const Vect& center)
{
	Vect campos;

	SceneManager::Get3DCamera()->getPos(campos);

	//rescale the indicator to adjust for camera distance
	rescaleFactor = std::abs((campos - center).mag()) / rescaleRateDividend;

	transform->position = Vect(center.X(), center.Y(), center.Z() - radius);

	displayRadiusDistance = radius;

	transform->scale = Matrix(SCALE, startingScale * rescaleFactor, startingScale * rescaleFactor, startingScale * rescaleFactor);

	transform->UpdateWorld();
}

void zPosUI::ForwardMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 1.0f, 0.0f);

	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	float newZ = mousedragloc.Z() + displayRadiusDistance;

	t->position = Vect(t->position.X(), t->position.Y(), newZ);
}

void zPosUI::BackwardMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 1.0f, 0.0f);

	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	float newZ = mousedragloc.Z() + displayRadiusDistance;

	t->position = Vect(t->position.X(), t->position.Y(), newZ);
}

void zPosUI::Selected()
{
	posUIcoll->SetIndicator(this);
}
