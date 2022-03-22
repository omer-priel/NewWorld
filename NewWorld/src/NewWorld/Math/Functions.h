#pragma once

#include "NewWorld/Math/Constants.h"

namespace NewWorld::Math
{
	inline float DegreesToRadians(float degrees)
	{
		return degrees / 180.0f * (float)PI;
	}

	inline float RadiansToDegrees(float radians)
	{
		return radians / (float)PI * 180.0f;
	}
}