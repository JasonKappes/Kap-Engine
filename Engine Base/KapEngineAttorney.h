#ifndef _kapengineattorney
#define _kapengineattorney

class KapEngineAttorney
{
	friend class FreezeTime;
	friend class Main;
private:

	class EngineTime
	{
		friend class FreezeTime;
	private:
		static float GetTime();

	private:
		EngineTime() = delete;
		EngineTime(const EngineTime&) = delete;
		EngineTime operator=(const EngineTime&) = delete;
		~EngineTime() = delete;
	};

private:
	KapEngineAttorney() = delete;
	KapEngineAttorney(const KapEngineAttorney&) = delete;
	KapEngineAttorney operator=(const KapEngineAttorney&) = delete;
	~KapEngineAttorney() = delete;
};

#endif _kapengineattorney
#pragma once
