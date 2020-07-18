#ifndef _commandbase
#define _commandbase

class CommandBase
{
public:
	virtual void Execute() = 0;

	CommandBase() = default;
	CommandBase(const CommandBase&) = delete;
	virtual ~CommandBase() {}
};

#endif _commandbase
#pragma once
