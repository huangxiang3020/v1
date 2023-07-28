#pragma once
#include <cstdint>
#include "ClassIDs.h"

class Object
{
private:
	static int32_t sNextId;

public:
	virtual ClassIDType getClassIDType() const
	{
		return ClassID(Object);
	}

public:
	Object();
	virtual ~Object();
	static int32_t getNextId();

protected:
	int32_t mId = 0;
};
