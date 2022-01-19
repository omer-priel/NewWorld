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
		static constexpr Color Blue = Color(0, 1, 0);
		static constexpr Color Green = Color(0, 0, 1);

		// Editor Colors
		static constexpr Color EditorBackground = Colors::Red;
	};
}