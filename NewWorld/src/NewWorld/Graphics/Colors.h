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
		static constexpr Color DarkGray = Color(0.25f, 0.25f, 0.25f);
		static constexpr Color LightGray = Color(0.75f, 0.75f, 0.75f);
		static constexpr Color Orange = Color(1.0f, 0.5f, 0.0f);
		static constexpr Color Pink = Color(1.0f, 0.625f, 0.625f);

		// Editor Colors
		static constexpr Color EditorBackground = Color(0.2f, 0.2f, 0.2f);
	};
}