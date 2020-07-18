#ifndef _selectiontestcommand
#define _selectiontestcommand
#include "SelectionTestCommandBase.h"

class Selectable;

class SelectionTestCommand : public SelectionTestCommandBase
{
public:
	SelectionTestCommand() = delete;
	SelectionTestCommand(const SelectionTestCommand&) = delete;
	~SelectionTestCommand() = default;

	SelectionTestCommand(Selectable*);

	void Execute(Touchable* t);

private:
	Selectable* m_selectable;
};

#endif _selectiontestcommand
#pragma once
