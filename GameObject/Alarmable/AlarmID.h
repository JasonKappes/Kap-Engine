#ifndef _alarmid
#define _alarmid
#include <map>

class Alarmable;

class Alarm
{
public:
	enum ID { _0, _1, _2 };

	using AlarmEvent = std::pair< Alarmable*, ID>;
	using TimeLineMap = std::multimap<float, AlarmEvent>;
	using StorageEntryRef = TimeLineMap::iterator;

	static const int NUMBER_OF_ALARMS = 3;

private:
	Alarm() = delete;
	Alarm(const Alarm&) = delete;
	Alarm operator=(const Alarm&) = delete;
	~Alarm() = delete;
};

#endif _alarmid
#pragma once
