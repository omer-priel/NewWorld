#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Graphics
{
	using Color = Vector4;
	using SolidColor = Vector3;

	namespace ColorFunctions
	{
		constexpr Color FromRGB(ushort red, ushort blue, ushort green, ushort alpha)
		{
			return Color(red / 255.0f, blue / 255.0f, green / 255.0f, alpha / 255.0f);
		}

		constexpr SolidColor FromRGB(ushort red, ushort blue, ushort green)
		{
			return SolidColor(red / 255.0f, blue / 255.0f, green / 255.0f);
		}

		constexpr Color FromRGB(uint rgb, ushort alpha)
		{
			return FromRGB(rgb / (256 * 256), (rgb / 256) % 256, rgb % 256, alpha);
		}

		constexpr SolidColor FromRGB(uint rgb)
		{
			return SolidColor(rgb / (256 * 256), (rgb / 256) % 256, rgb % 256);
		}
	}
}