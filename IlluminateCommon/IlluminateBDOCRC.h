#pragma once

#include "IlluminateTypes.h"

#include <algorithm>

class BDOCRC
{
public:
	BDOCRC();
	~BDOCRC();

	static UInt32 processString(std::string str, UInt32 type);

	static UInt32 processLowerString(std::string str, UInt32 type);

	static UInt32 process(UInt8* data, UInt32 length, UInt32 type);
};