#include "yPosUI.h"
#include "PositionUI.h"
#include "SceneManager.h"
#include "KapMathTools.h"
#include "OldPositionCommand.h"

yPosUI::~yPosUI()
{
	delete transform->object;
}

yPosUI::yPosUI(PositionUI* parent)
{
	this->selectable_transform = transform;

	posUIcoll = parent;

	transform->object = new GraphicsObject_TextureFlat(ModelManager::Get("position_ui.azul"), ShaderManager::Get("textureFlatRender"), TextureManager::Get("green.tga"));

	startingScale = 60.0f;
	rescaleRateDividend = 1500.0f;
	radiusSpread = 0.5f;

	transform->scale = Matrix(SCALE, startingScale, startingScale, startingScale);
	transform->rotation = Matrix(IDENTITY);
	transform->UpdateWorld();

	SelectableAttorney::Editor::SetSelectionModel(this, Selectable::Volume::BSPHERE);
	//SelectableAttorney::Editor::FastSceneRegistration(this);
}

void yPosUI::Display(float radius, const Vect& center)
{
	Vect campos;

	SceneManager::Get3DCamera()->getPos(campos);

	//rescale the indicator to adjust for camera distance
	rescaleFactor = std::abs((campos - center).mag()) / rescaleRateDividend;

	transform->position = Vect(center.X(), center.Y() + radius, center.Z());

	displayRadiusDistance = radius;

	transform->scale = Matrix(SCALE, startingScale * rescaleFactor, startingScale * rescaleFactor, startingScale * rescaleFactor);

	transform->UpdateWorld();
}

void yPosUI::ForwardMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldPositionCommand(*s, t->position));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 0.0f, 1.0f);

	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	float newY = mousedragloc.Y() - displayRadiusDistance;

	t->position = Vect(t->position.X(), newY, t->position.Z());
}

void yPosUI::BackwardMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldPositionCommand(*s, t->position));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 0.0f, 1.0f);

	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	float newY = mousedragloc.Y() - displayRadiusDistance;

	t->position = Vect(t->position.X(), newY, t->position.Z());
}

void yPosUI::Selected()
{
	posUIcoll->SetIndicator(this);
}
