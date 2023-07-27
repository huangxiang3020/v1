#pragma once
#include <cstdint>
#include <memory>
class Object
{
private:
	static int32_t sNextId;

public:
	Object();
	virtual ~Object();

protected:
	int32_t mId = 0;
};

