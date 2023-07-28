#pragma once
#include "ClassIDs.h"
#define	REGISTER_CLASS(x) \
public: \
	ClassIDType getClassID() const override { return ClassID(x);} \
	std::string getClassName() { return #x; }
