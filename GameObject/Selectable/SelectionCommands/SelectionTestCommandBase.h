#ifndef _selectiontestcommandbase
#define _selectiontestcommandbase

class Touchable;

class SelectionTestCommandBase
{
public:
	SelectionTestCommandBase() = default;
	SelectionTestCommandBase(const SelectionTestCommandBase&) = delete;
	virtual ~SelectionTestCommandBase() = default;

	virtual void Execute(Touchable*) = 0;

};

#endif _selectiontestcommandbase
#pragma once
