#pragma once

class TimeManger
{
public:
	static TimeManger& instance();
	TimeManger(const TimeManger&) = delete;
	TimeManger& operator=(const TimeManger&) = delete;
	void update();
	float getDeltaTime() const;
	float getTotalTime() const;

private:
	TimeManger();

	float mLastTime = 0;
	float mStartTime = 0;
	float mTotalTime = 0;
	float mDeltaTime = 0;
};
