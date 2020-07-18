#ifndef _rollbackhandlerattorney
#define _rollbackhandlerattorney

class PastEventCommand;

class RollbackHandlerAttorney
{
	friend class KapEngine;
	friend class EditorInput;
	friend class ActiveObject;
	friend class xPosUI;
	friend class yPosUI;
	friend class zPosUI;
	friend class xyzScaleUI;
	friend class zRotUI;
	friend class xRotUI;
	friend class yRotUI;
private:
	static void Delete();
	static void Rollback();
	static void LogEvent(PastEventCommand*);

private:
	RollbackHandlerAttorney() = delete;
	RollbackHandlerAttorney(const RollbackHandlerAttorney&) = delete;
	RollbackHandlerAttorney operator=(const RollbackHandlerAttorney&) = delete;
	virtual ~RollbackHandlerAttorney() = delete;
};

#endif _rollbackhandlerattorney
#pragma once
