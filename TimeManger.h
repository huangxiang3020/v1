#pragma once
#include <cstdint>

class TimeManger
{
public:
	static TimeManger& instance();
	TimeManger(const TimeManger&) = delete;
	TimeManger& operator=(const TimeManger&) = delete;
	void awake();
	void update();
	float getDeltaTime() const;

private:
	TimeManger() = default;
	int64_t mCurrentTime = 0;
	int64_t mLastTime = 0;
	int64_t mStartTime = 0;
	int64_t mPerfCountFreq = 0;

	double mTimeScale = 0;
	float mTotalTime = 0;
	float mDeltaTime = 0;
};
