#ifndef _timemanager
#define _timemanager

class FreezeTime;

class TimeManager
{
	friend class TimeManagerAttorney;
public: // --- >  ENGINE METHODS, USER METHODS

	/// <summary>
	/// This returns the current amount of game time elapsed.
	/// </summary> 
	/// \ingroup Time
	static float GetTime();

	/// <summary>
	/// This returns the time elapsed between the previous and current frame.
	/// </summary> 
	/// \ingroup Time
	static float GetFrameTime();

private:
	TimeManager();
	TimeManager(const TimeManager& w) = delete;
	TimeManager operator=(const TimeManager& w) = delete;
	~TimeManager();

	static TimeManager& Instance()
	{
		if (!m_ptrTimeManagerInstance)
		{
			m_ptrTimeManagerInstance = new TimeManager();
		}
		return *m_ptrTimeManagerInstance;
	}

	static void ProcessTime(float t_sysTime) { Instance().privProcessTime(t_sysTime); }
	static void Delete();

	void privProcessTime(float);

private:
	FreezeTime& m_ptrFreezeTime;
	static TimeManager* m_ptrTimeManagerInstance;
	float m_currentTime;
	float m_previousTime;
	float m_frameTime;
};

#endif _timemanager
#pragma once
