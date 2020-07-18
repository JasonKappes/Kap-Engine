#include "Transform.h"
#include "SceneManager.h"
#include "ModelManager.h"
#include "ShaderManager.h"

Transform::Transform() : position(), rotation(Matrix(IDENTITY)), scale(Matrix(IDENTITY)),
world(Matrix(IDENTITY)), center(Vect(0, 0, 0)), radius(1.0f), object(nullptr) {}

Transform::Transform(Transform* t_copy)
{
	this->position = Vect(t_copy->position);
	this->rotation = Matrix(t_copy->rotation);
	this->scale = Matrix(t_copy->scale);
	this->world = Matrix(t_copy->world);
	this->center = Vect(t_copy->center);
	this->radius = t_copy->radius;

	this->object = t_copy->object;
}

Transform::Transform(const Transform& t_copy)
{
	this->position	= Vect(t_copy.position);
	this->rotation	= Matrix(t_copy.rotation);
	this->scale		= Matrix(t_copy.scale);
	this->world		= Matrix(t_copy.world);
	this->center	= Vect(t_copy.center);
	this->radius	= t_copy.radius;

	//want to keep reference to the current graphics object
	this->object	= t_copy.object;
}

Transform Transform::operator=(const Transform& t_copy)
{
	this->position	= t_copy.position;
	this->rotation	= t_copy.rotation;
	this->scale		= t_copy.scale;
	this->world		= t_copy.world;
	this->center	= t_copy.center;
	this->radius	= t_copy.radius;
	this->object	= t_copy.object;

	return *this;
}

void Transform::Render()
{
	this->object->Render(SceneManager::Get3DCamera());
}

void Transform::SetGraphicsObject(GraphicsObject* t_go)
{
	this->object = t_go;
	UpdateWorld();
}

void Transform::UpdateWorld()
{
	this->center = object->getModel()->getCenter() * world;
	this->radius = object->getModel()->getRadius() * world.get(MatrixRowType::ROW_0).mag();
	world = scale * rotation * Matrix(TRANS, position);
	object->SetWorld(world);
}

float Transform::GetRadius() const
{
	return this->radius;
}

const Vect& Transform::GetCenter() const
{
	return this->center;
}

const Matrix& Transform::GetWorld() const
{
	return this->world;
}
