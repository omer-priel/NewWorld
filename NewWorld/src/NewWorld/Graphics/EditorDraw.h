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
		static void DrawLine(int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth = 1);

		static void DrawRectangle(int x, int y, uint width, uint height, const Graphics::Color& color);
		static void DrawOutlineRectangle(int x, int y, uint width, uint height, const Graphics::Color& color, uint lineWidth = 1);

		// Actions Global
	private:
		static void DrawLine(RawPointer<Editor::EditorWindow> window, int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth);

		static void DrawFillRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color);
		static void DrawOutlineRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color, uint lineWidth);

		// Utilities
	private:
		static void BeforeDraw();
		static void AfterDraw();
		
		static Vector4 GetCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y);

		static void AddCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y);
	};
}