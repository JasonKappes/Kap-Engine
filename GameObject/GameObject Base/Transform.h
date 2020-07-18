#ifndef _transform
#define _transform
#include "Matrix.h"
#include "GraphicsObject.h"

class Transform
{
public:
	Transform();
	Transform(Transform*);
	Transform(const Transform&);
	Transform operator=(const Transform&);
	~Transform() = default;

	void SetGraphicsObject(GraphicsObject*);

	void UpdateWorld();
	void Render();

	float GetRadius() const;
	const Vect& GetCenter() const;
	const Matrix& GetWorld() const;

public:
	Vect position;
	Matrix rotation;
	Matrix scale;
	GraphicsObject* object;

private:
	//GraphicsObject* object;
	Matrix world;
	Vect center;
	float radius;
};


#endif _transform
#pragma once
