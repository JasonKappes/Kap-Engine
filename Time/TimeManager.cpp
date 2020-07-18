#include "TimeManager.h"
#include "FreezeTime.h"
#include <DebugOut.h>

TimeManager* TimeManager::m_ptrTimeManagerInstance = nullptr;

TimeManager::TimeManager() : m_frameTime(0), m_previousTime(0), m_currentTime(0), m_ptrFreezeTime(*(new FreezeTime())) {}

TimeManager::~TimeManager() { delete &this->m_ptrFreezeTime; }

float TimeManager::GetTime() { return Instance().m_currentTime; }

float TimeManager::GetFrameTime() { return Instance().m_frameTime; }

void TimeManager::Delete() { delete Instance().m_ptrTimeManagerInstance; }

void TimeManager::privProcessTime(float t_systemTime)
{
	 //Time Updates
	this->m_previousTime = this->m_currentTime;
	this->m_currentTime = this->m_ptrFreezeTime.GetTimeInSeconds(t_systemTime);
	this->m_frameTime = this->m_currentTime - this->m_previousTime;
	DebugMsg::out("TotalTime: %.2f s lastFrame: %.4f s (%.0f FPS)\n", this->m_currentTime, this->m_frameTime, 1 / this->m_frameTime);
}