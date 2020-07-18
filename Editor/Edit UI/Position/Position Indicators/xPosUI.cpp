#include "xPosUI.h"
#include "SceneManager.h"
#include "KapMathTools.h"
#include "PositionUI.h"
#include "RollbackHandlerAttorney.h"
#include "Serializable.h"
#include "OldPositionCommand.h"

xPosUI::~xPosUI()
{
	delete transform->object;
}

xPosUI::xPosUI(PositionUI* parent)
{
	this->selectable_transform = transform;

	posUIcoll = parent;

	transform->object = new GraphicsObject_TextureFlat(ModelManager::Get("position_ui.azul"), ShaderManager::Get("textureFlatRender"), TextureManager::Get("red.tga"));

	startingScale = 60.0f;
	rescaleRateDividend = 1500.0f;
	radiusSpread = 0.15f;

	transform->scale = Matrix(SCALE, startingScale, startingScale, startingScale);
	transform->rotation = Matrix(RotType::ROT_Z, 1.64f);
	transform->UpdateWorld();

	SelectableAttorney::Editor::SetSelectionModel(this, Selectable::Volume::BSPHERE);
}

void xPosUI::Display(float radius, const Vect& center)
{	
	Vect campos;
	
	SceneManager::Get3DCamera()->getPos(campos);
	
	//rescale the indicator to adjust for camera distance
	rescaleFactor = std::abs((campos - center).mag()) / rescaleRateDividend;

	transform->position = Vect(center.X() - radius, center.Y(), center.Z());

	displayRadiusDistance = radius;

	transform->scale = Matrix(SCALE, startingScale * rescaleFactor, startingScale * rescaleFactor, startingScale * rescaleFactor);
		
	transform->UpdateWorld();
}

void xPosUI::Selected()
{
	posUIcoll->SetIndicator(this);
}

void xPosUI::LeftMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldPositionCommand(*s, t->position));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 1.0f, 0.0f);

	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	float newX = mousedragloc.X() + displayRadiusDistance;

	t->position = Vect(newX, t->position.Y(), t->position.Z());
}

void xPosUI::RightMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldPositionCommand(*s, t->position));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 1.0f, 0.0f);

	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	float newX = mousedragloc.X() + displayRadiusDistance;

	t->position = Vect(newX, t->position.Y(), t->position.Z());
}
