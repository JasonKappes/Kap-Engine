#include "RollbackHandler.h"
#include "PastEventCommand.h"
#include <DebugOut.h>

RollbackHandler* RollbackHandler::m_ptrInstance = nullptr;

RollbackHandler::~RollbackHandler()
{
	while (!eventColl.empty())
	{
		delete Instance().eventColl.top();
		eventColl.pop();
	}

	DebugMsg::out(" ROLLBACK HANDLER: stack size %d ", eventColl.size());
}

void RollbackHandler::Rollback()
{
	if (!Instance().eventColl.empty())
	{
		Instance().eventColl.top()->Execute();
		delete Instance().eventColl.top();
		Instance().eventColl.pop();
	}
}

void RollbackHandler::LogEvent(PastEventCommand* pastCommand)
{
	Instance().eventColl.push(pastCommand);
}

void RollbackHandler::Delete()
{
	delete Instance().m_ptrInstance;
}

