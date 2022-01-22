#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Graphics/Color.h"

namespace NewWorld::Graphics
{
	// This is static class
	class Colors : public Object
	{
	NW_CLASS(NewWorld::Graphics, Colors)

		// Basic Colors
	public:
		static constexpr Color Black = Color(0, 0, 0);
		static constexpr Color White = Color(1, 1, 1);

		static constexpr Color Red = Color(1, 0, 0);
		static constexpr Color Green = Color(0, 1, 0);
		static constexpr Color Blue = Color(0, 0, 1);

		// Simple Colors
		static constexpr Color Cyan = Color(0, 1, 1);
		static constexpr Color Magenta = Color(1, 0, 1);
		static constexpr Color Yellow = Color(1, 1, 0);
		static constexpr Color Gray = Color(0.5f, 0.5f, 0.5f);
		static constexpr Color Orange = Color(1.0f, 0.5f, 0.0f);
		static constexpr Color Pink = Color(1.0f, 0.625f, 0.625f);
		static constexpr Color Gold = ColorFunctions::FromRGB(255, 215, 0);

		static constexpr Color DarkRed = Color(0.5f, 0.0f, 0.0f); // rgb(139,0,0)
		static constexpr Color Ruby = ColorFunctions::FromRGB(155, 17, 30);
		static constexpr Color NeonRed = ColorFunctions::FromRGB(185, 46, 52);
		static constexpr Color RoseRed = ColorFunctions::FromRGB(194, 30, 86);
		static constexpr Color Coral = ColorFunctions::FromRGB(248, 131, 121);

		static constexpr Color DarkGreen = Color(0.0f, 0.25f, 0.0f); //rgb(0, 100, 0)
		static constexpr Color ForestGreen = ColorFunctions::FromRGB(34, 139, 34);
		static constexpr Color LimeGreen = ColorFunctions::FromRGB(50, 205, 50);
		static constexpr Color KellyGreen = ColorFunctions::FromRGB(76, 187, 23);
		static constexpr Color LightGreen = ColorFunctions::FromRGB(144, 238, 144);

		static constexpr Color NavyBlue = Color(0.0f, 0.0f, 0.5f);
		static constexpr Color CobaltBlue = ColorFunctions::FromRGB(0, 71, 171);
		static constexpr Color RoyalBlue = ColorFunctions::FromRGB(0, 35, 102);
		static constexpr Color LightBlue = ColorFunctions::FromRGB(173, 216, 230);
		static constexpr Color Turquoise = ColorFunctions::FromRGB(64, 224, 208);

		static constexpr Color DarkGray = Color(0.25f, 0.25f, 0.25f);
		static constexpr Color LightGray = Color(0.75f, 0.75f, 0.75f);
		static constexpr Color Charcoal = ColorFunctions::FromRGB(54, 69, 79);
		static constexpr Color SlateGray = ColorFunctions::FromRGB(119, 136, 153);
		static constexpr Color Silver = ColorFunctions::FromRGB(192, 192, 192);


		// Editor Colors
		static constexpr Color EditorBackground = Color(0.2f, 0.2f, 0.2f);
	};
}