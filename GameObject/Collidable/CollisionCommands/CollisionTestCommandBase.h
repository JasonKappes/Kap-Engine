#ifndef _collisiontestcommandbase
#define _collisiontestcommandbase

class CollisionTestCommandBase
{
public:
	CollisionTestCommandBase() = default;
	CollisionTestCommandBase(const CollisionTestCommandBase&) = delete;
	virtual ~CollisionTestCommandBase() {}

public:
	virtual void Execute() = 0;

};

#endif _collisiontestcommandbase
#pragma once
