#include "TimeManger.h"
#include <GLFW/glfw3.h>

TimeManger::TimeManger()
{
	mStartTime = static_cast<float>(glfwGetTime());
}

TimeManger& TimeManger::instance()
{
	static TimeManger instance;
	return instance;
}

void TimeManger::update()
{
	const auto currentTime = static_cast<float>(glfwGetTime());
	mDeltaTime = currentTime - mLastTime;
	mLastTime = currentTime;
	mTotalTime = currentTime - mStartTime;
}

float TimeManger::getDeltaTime() const
{
	return mDeltaTime;
}

float TimeManger::getTotalTime() const
{
	return mTotalTime;
}
