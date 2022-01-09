#pragma once

//#include "NewWorld/Minimal.h" 
// TEMP:
#include "NewWorld/DataTypes/Primitives.h"

namespace NewWorld::Debug
{
	enum class LogLevel : DataTypes::Byte
	{
		Critical = 0,
		Error = 1,
		Warning = 2,
		Info = 3,
		Debug = 4
	};
}