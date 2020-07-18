// FreezeTime
// Andre Berthiaume, Jan 2016

#ifndef _FreezeTime
#define _FreezeTime

#include "AzulCore.h"

class FreezeTime
{
	friend class KapEngine;

public: // --- > ENGINE METHODS
	float GetTimeInSeconds(float sys_time);
	static bool HackedKeyRelease(AZUL_KEY k);

public:
	FreezeTime();
	~FreezeTime() = default;
	FreezeTime(const FreezeTime&) = delete;
	FreezeTime& operator=(const FreezeTime&) = delete;

private:
	/// <summary>
	/// If the 'F' key is pressed, the engine will freeze and no managers will be called.
	/// 
	/// Letting go of the key resumes the calls to the managers, and the game continues where it left off.
	/// </summary> 
	/// \ingroup Time
	static const AZUL_KEY FREEZE_KEY = AZUL_KEY::KEY_F;
	static const AZUL_KEY SINGLE_FRAME_KEY = AZUL_KEY::KEY_F9;

	float totalFrozenTime;
	bool freeze_mode_active;

	float WaitAndReturnFrozenTime(float activetime);

};

#endif _FreezeTime