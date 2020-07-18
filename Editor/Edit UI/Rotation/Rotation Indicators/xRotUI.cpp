#include "xRotUI.h"
#include "SceneManager.h"
#include "KapMathTools.h"
#include "RotationUI.h"
#include "CollisionVolumeOBB.h"
#include "VisualizerAttorney.h"
#include "OldRotationCommand.h"
#include "Cursor.h"

xRotUI::~xRotUI()
{
	delete this->transform->object;
}

xRotUI::xRotUI(RotationUI* parent)
{
	this->selectable_transform = transform;
	rotUIcoll = parent;

	transform->object = new GraphicsObject_TextureFlat(ModelManager::Get("rotation_ui.azul"), ShaderManager::Get("textureFlatRender"), TextureManager::Get("red.tga"));

	startingScale = 1.75f;
	rescaleRateDividend = 6.5f;
	radiusSpread = 0.1f;

	rotationSlowFactor = 0.01f;

	modelRadius = transform->object->getModel()->getRadius();

	transform->scale = Matrix(SCALE, startingScale, startingScale, startingScale);
	transform->rotation = Matrix(IDENTITY);
	transform->UpdateWorld();

	SelectableAttorney::Editor::SetSelectionModel(this, Selectable::Volume::OBB);
	//SelectableAttorney::Editor::FastSceneRegistration(this);
}

void xRotUI::Display(float radius, const Vect& center)
{
	Vect campos;

	SceneManager::Get3DCamera()->getPos(campos);

	//rescale the indicator to adjust for camera distance
	rescaleFactor = std::abs((campos - center).mag()) / rescaleRateDividend;

	rescaleFactor += radius + this->modelRadius;

	transform->position = Vect(center.X(), center.Y(), center.Z());

	transform->scale = Matrix(SCALE, startingScale * rescaleFactor, startingScale * rescaleFactor, startingScale * rescaleFactor);

	transform->UpdateWorld();

}

void xRotUI::Selected()
{
	rotUIcoll->SetIndicator(this);
}

void xRotUI::LeftMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 1.0f, 0.0f);

	float rotationAmount = ((float)Cursor::GetLeftCursorMovementAmount()) * rotationSlowFactor;

	//get what side camera is on
	Vect diff = raypoint - transform->position;

	//get mouse intersection below/above half 
	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	if (diff.Z() < 0) {
		if (mousedragloc.Z() < transform->position.Z()) rotationAmount *= -1.0f;
	}
	else {
		if (mousedragloc.Z() > transform->position.Z()) rotationAmount *= -1.0f;
	}

	if (diff.Y() < 0) rotationAmount *= -1.0f;

	t->rotation *= Matrix(RotType::ROT_Y, rotationAmount);
}

void xRotUI::RightMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 1.0f, 0.0f);

	float rotationAmount = ((float)Cursor::GetRightCursorMovementAmount()) * rotationSlowFactor;

	//get what side camera is on
	Vect diff = raypoint - transform->position;

	//get mouse intersection below/above half 
	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	if (diff.Z() < 0) {
		if (mousedragloc.Z() < transform->position.Z()) rotationAmount *= -1.0f;
	}
	else {
		if (mousedragloc.Z() > transform->position.Z()) rotationAmount *= -1.0f;
	}

	if (diff.Y() < 0) rotationAmount *= -1.0f;

	t->rotation *= Matrix(RotType::ROT_Y, -rotationAmount);
}

void xRotUI::ForwardMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 1.0f, 0.0f);

	float rotationAmount = ((float)Cursor::GetUpCursorMovementAmount()) * rotationSlowFactor;

	//get what side camera is on
	Vect diff = raypoint - transform->position;

	//get mouse intersection below/above half 
	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	if (diff.Z() < 0) {
		if (mousedragloc.X() < transform->position.X()) rotationAmount *= -1.0f;
	}
	else {
		if (mousedragloc.X() > transform->position.X()) rotationAmount *= -1.0f;
	}

	t->rotation *= Matrix(RotType::ROT_Y, -rotationAmount);
}

void xRotUI::BackwardMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(0.0f, 1.0f, 0.0f);

	float rotationAmount = ((float)Cursor::GetDownCursorMovementAmount()) * rotationSlowFactor;

	//get what side camera is on
	Vect diff = raypoint - transform->position;

	//get mouse intersection below/above half 
	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	if (diff.Z() < 0) {
		if (mousedragloc.X() < transform->position.X()) rotationAmount *= -1.0f;
	}
	else {
		if (mousedragloc.X() > transform->position.X()) rotationAmount *= -1.0f;
	}

	t->rotation *= Matrix(RotType::ROT_Y, rotationAmount);
}


