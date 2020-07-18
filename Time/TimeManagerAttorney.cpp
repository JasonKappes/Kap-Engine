#include "TimeManagerAttorney.h"
#include "TimeManager.h"

void TimeManagerAttorney::Delete()
{
	TimeManager::Delete();
}

void TimeManagerAttorney::ProcessTime(float t_sysTime)
{
	TimeManager::ProcessTime(t_sysTime);
}
