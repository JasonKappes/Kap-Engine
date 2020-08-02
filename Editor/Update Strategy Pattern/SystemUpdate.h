#ifndef _systemupdate
#define _systemupdate

//Update strategy pattern base class.
//The derived child of this class defines what systems are being updated during a world-edit or regular run.
class SystemUpdate
{
public:
	virtual void Tick() const = 0;

public:
	SystemUpdate() = default;
	SystemUpdate(const SystemUpdate&) = delete;
	virtual ~SystemUpdate() = default;
};

#endif _systemupdate
#pragma once
