#include "SelectionVolumeBsphere.h"
#include "Raycast.h"
#include "Transform.h"

SelectionVolumeBsphere::SelectionVolumeBsphere(const Transform* t)
{
	this->objtransform = t;
}

bool SelectionVolumeBsphere::MouseSelectionIntersection()
{
	return Raycast::MouseSphereCollision(this->objtransform->position, this->objtransform->GetRadius());
}
