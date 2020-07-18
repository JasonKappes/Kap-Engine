#ifndef _systemupdate
#define _systemupdate

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
