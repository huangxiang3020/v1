#pragma once
#include <cstdint>
#include <string>

#include "ClassIDs.h"

class Object
{
	static int32_t sNextId;

public:
	virtual std::string getClassName() { return "Object"; }
	virtual ClassIDType getClassID() const { return ClassID(Object); }
	int32_t getID() const { return mID; }
	Object();
	Object(const Object& object) = delete;
	Object& operator =(const Object& object) = delete;

protected:
	virtual ~Object();
	int32_t mID = 0;
};
