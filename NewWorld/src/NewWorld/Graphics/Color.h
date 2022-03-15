#pragma once

#include "NewWorld/Minimal.h"

namespace NewWorld::Graphics
{
	using Color = Vector4;
	using SolidColor = Vector3;

	namespace ColorFunctions
	{
		constexpr Color FromRGBA(ushort red, ushort blue, ushort green, ushort alpha = 255)
		{
			return Color(red / 255.0f, blue / 255.0f, green / 255.0f, alpha / 255.0f);
		}

		constexpr SolidColor FromRGB(ushort red, ushort blue, ushort green)
		{
			return SolidColor(red / 255.0f, blue / 255.0f, green / 255.0f);
		}

		constexpr Color FromRGBA(uint rgb, ushort alpha = 255)
		{
			return FromRGBA(rgb / (256 * 256), (rgb / 256) % 256, rgb % 256, alpha);
		}

		constexpr SolidColor FromRGB(uint rgb)
		{
			return SolidColor(rgb / (256 * 256), (rgb / 256) % 256, rgb % 256);
		}
	}
}