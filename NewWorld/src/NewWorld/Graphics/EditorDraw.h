#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Graphics/Color.h"

namespace NewWorld::Graphics
{
	// This is static class
	class EditorDraw : public Object
	{
	NW_CLASS(NewWorld::Graphics, EditorDraw)

		// Actions
	public:
		static void DrawRectangle(uint x, uint y, uint width, uint height, const Graphics::Color& color);
	};
}