#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Graphics
{
	using Color = Vector3;

	namespace ColorFunctions
	{
		constexpr Color FromRGB(ushort red, ushort blue, ushort green)
		{
			return Color(red / 255.0f, blue / 255.0f, green / 255.0f);
		}

		constexpr Color FromRGB(uint rgb)
		{
			return FromRGB(rgb / (256 * 256), (rgb / 256) % 256, rgb % 256);
		}
	}
}