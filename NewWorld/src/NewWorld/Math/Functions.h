#pragma once

#include "NewWorld/Math/Constants.h"

namespace NewWorld::Math
{
	inline float DegreesToRadians(float degrees)
	{
		return degrees / 180 * PI;
	}

	inline float RadiansToDegrees(float radians)
	{
		return radians / PI * 180;
	}
}