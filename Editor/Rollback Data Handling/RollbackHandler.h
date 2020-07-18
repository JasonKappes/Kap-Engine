#ifndef _rollbackhandler
#define _rollbackhandler
#include <stack>

class PastEventCommand;

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

	static void Rollback();
	static void LogEvent(PastEventCommand*);
	static void Delete();

private:
	static RollbackHandler* m_ptrInstance;
	std::stack<PastEventCommand*> eventColl;
};

#endif _rollbackhandler
#pragma once
