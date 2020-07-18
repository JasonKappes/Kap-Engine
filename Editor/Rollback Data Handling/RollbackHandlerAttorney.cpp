#include "RollbackHandlerAttorney.h"
#include "RollbackHandler.h"

void RollbackHandlerAttorney::Delete()
{
	RollbackHandler::Delete();
}

void RollbackHandlerAttorney::Rollback()
{
	RollbackHandler::Rollback();
}

void RollbackHandlerAttorney::LogEvent(PastEventCommand* c)
{
	RollbackHandler::LogEvent(c);
}
