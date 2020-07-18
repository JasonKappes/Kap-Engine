#ifndef _visualizetestcommandbase
#define _visualizetestcommandbase
#include "Vect.h"
#include "Matrix.h"

class VisualizeTestCommandBase : public Align16
{
public:
	VisualizeTestCommandBase() = default;
	VisualizeTestCommandBase(const VisualizeTestCommandBase&) = delete;
	virtual ~VisualizeTestCommandBase() {}

public:
	virtual void Execute() = 0;

};

#endif _visualizetestcommandbase
#pragma once
