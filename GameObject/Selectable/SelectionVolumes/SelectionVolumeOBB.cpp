#include "SelectionVolumeOBB.h"
#include "Raycast.h"
#include "Transform.h"
#include "CollisionVolumeOBB.h"
#include "VisualizerAttorney.h"
#include <DebugOut.h>
#include "Selectable.h"

SelectionVolumeOBB::SelectionVolumeOBB(const Transform* t)
{

	//DebugMsg::out("\n CONSTR min %3.2f %3.2f %3.2f %3.2f, max %3.2f %3.2f %3.2f %3.2f", minn.X(), minn.Y(), minn.Z(), minn.W(), maxx.X(), maxx.Y(), maxx.Z(), maxx.W());
	this->objtransform = t;
	Vect minn = objtransform->object->getModel()->getMinAABB();
	Vect maxx = objtransform->object->getModel()->getMaxAABB();
}

bool SelectionVolumeOBB::MouseSelectionIntersection()
{
	Vect minnn = objtransform->object->getModel()->getMinAABB();
	Vect maxxx = objtransform->object->getModel()->getMaxAABB();

	this->min = minnn * objtransform->GetWorld();
	this->max = maxxx * objtransform->GetWorld();

	return Raycast::MouseBoxCollision(this->min, this->max);
}


