#ifndef _rollbackhandler
#define _rollbackhandler
#include <stack>

class PastEventCommand;

//World-edit mode class
//Triggers rollback commands that can undo world-information changes
class RollbackHandler
{
	friend class RollbackHandlerAttorney;
private:
	RollbackHandler() = default;
	RollbackHandler(const RollbackHandler&) = delete;
	RollbackHandler operator=(const RollbackHandler&) = delete;
	~RollbackHandler();

	static RollbackHandler& Instance()
	{
		if (!m_ptrInstance)
			m_ptrInstance = new RollbackHandler();
		return *m_ptrInstance;
	}

	//This executes the most recent world-edit change command
	static void Rollback();
	
	//Adds a world-edit command to the stack
	static void LogEvent(PastEventCommand*);
	static void Delete();

private:
	static RollbackHandler* m_ptrInstance;
	std::stack<PastEventCommand*> eventColl;
};

#endif _rollbackhandler
#pragma once
