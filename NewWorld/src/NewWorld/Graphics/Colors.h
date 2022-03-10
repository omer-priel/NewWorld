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
		static constexpr Color Black = Color(0, 0, 0, 1);
		static constexpr Color White = Color(1, 1, 1, 1);
		static constexpr Color Transparency = Color(0, 0, 0, 0);

		static constexpr Color Red = Color(1, 0, 0, 1);
		static constexpr Color Green = Color(0, 1, 0, 1);
		static constexpr Color Blue = Color(0, 0, 1, 1);

		// Simple Colors
		static constexpr Color Cyan = Color(0, 1, 1, 1);
		static constexpr Color Magenta = Color(1, 0, 1, 1);
		static constexpr Color Yellow = Color(1, 1, 0, 1);
		static constexpr Color Gray = Color(0.5f, 0.5f, 0.5f, 1);
		static constexpr Color Orange = Color(1.0f, 0.5f, 0.0f, 1);
		static constexpr Color Pink = Color(1.0f, 0.625f, 0.625f, 1);
		static constexpr Color Gold = ColorFunctions::FromRGBA(255, 215, 0);

		static constexpr Color DarkRed = Color(0.5f, 0.0f, 0.0f, 1); // rgb(139,0,0)
		static constexpr Color Ruby = ColorFunctions::FromRGBA(155, 17, 30);
		static constexpr Color NeonRed = ColorFunctions::FromRGBA(185, 46, 52);
		static constexpr Color RoseRed = ColorFunctions::FromRGBA(194, 30, 86);
		static constexpr Color Coral = ColorFunctions::FromRGBA(248, 131, 121);

		static constexpr Color DarkGreen = Color(0.0f, 0.25f, 0.0f, 1); //rgb(0, 100, 0)
		static constexpr Color ForestGreen = ColorFunctions::FromRGBA(34, 139, 34);
		static constexpr Color LimeGreen = ColorFunctions::FromRGBA(50, 205, 50);
		static constexpr Color KellyGreen = ColorFunctions::FromRGBA(76, 187, 23);
		static constexpr Color LightGreen = ColorFunctions::FromRGBA(144, 238, 144);

		static constexpr Color NavyBlue = Color(0.0f, 0.0f, 0.5f, 1);
		static constexpr Color CobaltBlue = ColorFunctions::FromRGBA(0, 71, 171);
		static constexpr Color RoyalBlue = ColorFunctions::FromRGBA(0, 35, 102);
		static constexpr Color LightBlue = ColorFunctions::FromRGBA(173, 216, 230);
		static constexpr Color Turquoise = ColorFunctions::FromRGBA(64, 224, 208);

		static constexpr Color DarkGray = Color(0.25f, 0.25f, 0.25f, 1);
		static constexpr Color LightGray = Color(0.75f, 0.75f, 0.75f, 1);
		static constexpr Color Charcoal = ColorFunctions::FromRGBA(54, 69, 79);
		static constexpr Color SlateGray = ColorFunctions::FromRGBA(119, 136, 153);
		static constexpr Color Silver = ColorFunctions::FromRGBA(192, 192, 192);


		// Editor Colors
		static constexpr Color EditorBackground = Color(0.2f, 0.2f, 0.2f, 1);
	};
}