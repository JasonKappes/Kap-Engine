#include "zRotUI.h"
#include "SceneManager.h"
#include "KapMathTools.h"
#include "RotationUI.h"
#include "CollisionVolumeOBB.h"
#include "VisualizerAttorney.h"
#include "Cursor.h"
#include "OldRotationCommand.h"

zRotUI::~zRotUI()
{
	delete this->transform->object;
}

zRotUI::zRotUI(RotationUI* parent)
{
	this->selectable_transform = transform;
	rotUIcoll = parent;

	transform->object = new GraphicsObject_TextureFlat(ModelManager::Get("rotation_ui.azul"), ShaderManager::Get("textureFlatRender"), TextureManager::Get("blue.tga"));

	startingScale = 1.0f;
	rescaleRateDividend = 6.5f;
	radiusSpread = 0.1f;

	rotationSlowFactor = 0.01f;

	modelRadius = transform->object->getModel()->getRadius();

	transform->scale = Matrix(SCALE, startingScale, startingScale, startingScale);
	transform->rotation = Matrix(RotType::ROT_Z, 1.55f);
	transform->UpdateWorld();

	SelectableAttorney::Editor::SetSelectionModel(this, Selectable::Volume::OBB);
}

void zRotUI::Display(float radius, const Vect& center)
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


void zRotUI::Selected()
{
	rotUIcoll->SetIndicator(this);
}

void zRotUI::LeftMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(1.0f, 0.0f, 0.0f);

	float rotationAmount = ((float)Cursor::GetLeftCursorMovementAmount()) * rotationSlowFactor;

	//get what side camera is on
	Vect diff = raypoint - transform->position;

	//get mouse intersection below/above half 
	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	if (diff.X() > 0) rotationAmount *= -1.0f;

	if (mousedragloc.Y() < transform->position.Y()) rotationAmount *= -1.0f;

	t->rotation *= Matrix(RotType::ROT_X, -rotationAmount);
}

void zRotUI::RightMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(1.0f, 0.0f, 0.0f);

	float rotationAmount = ((float)Cursor::GetRightCursorMovementAmount()) * rotationSlowFactor;

	//get what side camera is on
	Vect diff = raypoint - transform->position;

	//get mouse intersection below/above half 
	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	if (diff.X() > 0) rotationAmount *= -1.0f;

	if (mousedragloc.Y() < transform->position.Y()) rotationAmount *= -1.0f;

	t->rotation *= Matrix(RotType::ROT_X, rotationAmount);
}

void zRotUI::ForwardMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(1.0f, 0.0f, 0.0f);

	float rotationAmount = ((float)Cursor::GetUpCursorMovementAmount()) * rotationSlowFactor;

	//get what side camera is on
	Vect diff = raypoint - transform->position;

	//get mouse intersection below/above half 
	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	if (diff.X() < 0)
	{
		if (mousedragloc.Z() > transform->position.Z())	rotationAmount *= -1.0f;
	}
	else {
		if (mousedragloc.Z() > transform->position.Z()) rotationAmount *= -1.0f;
	}

	t->rotation *= Matrix(RotType::ROT_X, rotationAmount);
}

void zRotUI::BackwardMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldRotationCommand(*s, t->rotation));

	Vect raypoint;

	SceneManager::Get3DCamera()->getPos(raypoint);

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect planenormal = Vect(1.0f, 0.0f, 0.0f);

	float rotationAmount = ((float)Cursor::GetDownCursorMovementAmount()) * rotationSlowFactor;

	//get what side camera is on
	Vect diff = raypoint - transform->position;

	//get mouse intersection below/above half 
	Vect mousedragloc = KapMathTools::LinePlaneIntersection(raypoint, raydirection, transform->position, planenormal);

	if (diff.X() < 0)
	{
		if (mousedragloc.Z() > transform->position.Z())	rotationAmount *= -1.0f;
	}
	else {
		if (mousedragloc.Z() > transform->position.Z()) rotationAmount *= -1.0f;
	}

	t->rotation *= Matrix(RotType::ROT_X, -rotationAmount);
}