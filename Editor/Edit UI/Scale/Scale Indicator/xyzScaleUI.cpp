#include "xyzScaleUI.h"
#include "SceneManager.h"
#include "KapMathTools.h"
#include "ScaleUI.h"
#include "CollisionVolumeOBB.h"
#include "VisualizerAttorney.h"
#include "OldScaleCommand.h"
#include "Cursor.h"

xyzScaleUI::~xyzScaleUI()
{
	delete this->transform->object;
}

xyzScaleUI::xyzScaleUI(ScaleUI* parent)
{
	this->selectable_transform = transform;
	scaleUIcoll = parent;

	transform->object = new GraphicsObject_TextureFlat(ModelManager::Get("scale_ui.azul"), ShaderManager::Get("textureFlatRender"), TextureManager::Get("white.tga"));

	startingScale = 60.0f;
	radiusSpread = 1.5f;
	rescaleRateDividend = 40'000.0f;
	scaleRate = 0.1f;

	modelRadius = transform->object->getModel()->getRadius();

	transform->scale = Matrix(SCALE, startingScale, startingScale, startingScale);
	transform->UpdateWorld();

	SelectableAttorney::Editor::SetSelectionModel(this, Selectable::Volume::OBB);
}

void xyzScaleUI::Display(float radius, const Vect& center)
{
	transform->position = Vect(center.X(), center.Y(), center.Z() + (radius*2.0f));

	float scaleFactor = (radius / this->modelRadius) * radiusSpread;

	Vect campos;

	SceneManager::Get3DCamera()->getPos(campos);

	float scaleoffset = (KapMathTools::Magnitude(campos) - KapMathTools::Magnitude(transform->position)) / rescaleRateDividend;

	//clamp min size
	if (scaleoffset < 0.75f) scaleoffset = 0.75f;

	transform->scale = Matrix(SCALE, scaleFactor, scaleFactor, scaleFactor);

	if (transform->scale.get(MatrixRowType::ROW_0).X() < 10.0f)
	{
		transform->scale = Matrix(SCALE, 10.0f, 10.0f, 10.0f);
	}

	transform->UpdateWorld();
}

void xyzScaleUI::Selected()
{
	scaleUIcoll->SetIndicator(this);
}

void xyzScaleUI::LeftMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldScaleCommand(*s, t->scale));

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect diff = raydirection - transform->position;

	float scaleAmount = ((float)Cursor::GetLeftCursorMovementAmount()) * scaleRate;

	if (scaleAmount < 0.95f) scaleAmount = 0.95f;

	if (scaleAmount > 1.0f)  scaleAmount = 0.99f;

	t->scale *= Matrix(SCALE, scaleAmount, scaleAmount, scaleAmount);
}

void xyzScaleUI::RightMovement(Serializable* s)
{
	Transform* t = SerializableAttorney::GameLoop::GetTransform(s);

	RollbackHandlerAttorney::LogEvent(new OldScaleCommand(*s, t->scale));

	Vect raydirection = Raycast::GetMouseWorldSpaceRay();

	Vect diff = raydirection - transform->position;

	float scaleAmount = ((float)Cursor::GetRightCursorMovementAmount()) * scaleRate;

	if ((1.0f + scaleAmount) > 1.05f) scaleAmount = 1.05f;

	if (scaleAmount < 1.0f) scaleAmount = 1.01f;

	t->scale *= Matrix(SCALE, scaleAmount, scaleAmount, scaleAmount);
}