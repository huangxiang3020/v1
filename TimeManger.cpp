#include "TimeManger.h"
#include <windows.h>

TimeManger& TimeManger::instance()
{
	static TimeManger instance;
	return instance;
}

void TimeManger::awake()
{
	QueryPerformanceFrequency(reinterpret_cast<LARGE_INTEGER*>(&mPerfCountFreq));
	mTimeScale = 1.0 / static_cast<double>(mPerfCountFreq);
	mTotalTime = 0;
	mDeltaTime = 0;
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mLastTime));
	mStartTime = mLastTime;
}

void TimeManger::update()
{
	QueryPerformanceCounter(reinterpret_cast<LARGE_INTEGER*>(&mCurrentTime));
	mDeltaTime = static_cast<float>((static_cast<double>(mCurrentTime) - static_cast<double>(mLastTime)) * mTimeScale);
	mLastTime = mCurrentTime;
	mTotalTime = static_cast<float>((static_cast<double>(mCurrentTime) - static_cast<double>(mStartTime)) * mTimeScale);
}

float TimeManger::getDeltaTime() const
{
	return mDeltaTime;
}
