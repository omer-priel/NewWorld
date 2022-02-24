#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/LocalPainter.h"
#include "NewWorld/Editor/EditorWindow.h"

namespace NewWorld::Graphics
{
	// This is static class
	class EditorDraw : public Object
	{
	NW_CLASS(NewWorld::Graphics, EditorDraw)

		// Actions Local
	public:
		static void DrawRectangle(int x, int y, uint width, uint height, const Graphics::Color& color);
		static void DrawLine(int x1, int y1, int x2, int y2, const Graphics::Color& color);

		// Actions Global
	private:
		static void DrawRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color);
		static void DrawLine(RawPointer<Editor::EditorWindow> window, int x1, int y1, int x2, int y2, const Graphics::Color& color);

		// Utilities
	private:
		static Vector4 GetCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y);

		static void AddCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y);
	};
}