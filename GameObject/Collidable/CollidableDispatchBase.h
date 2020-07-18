#ifndef _collidabledispatchbase
#define _collidabledispatchbase

class Collidable;

class CollidableDispatchBase
{
public:
	CollidableDispatchBase() = default;
	CollidableDispatchBase(const CollidableDispatchBase&) = delete;
	virtual ~CollidableDispatchBase() {}

	virtual void ProcessCallbacks(Collidable*, Collidable*) {};

	virtual void ProcessCallbacks(Collidable*) {}
};

#endif _collidabledispatchbase
#pragma once
