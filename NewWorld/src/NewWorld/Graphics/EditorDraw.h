#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Editor/EditorWindow.h"

namespace NewWorld::Graphics
{
	// This is static class
	class EditorDraw : public Object
	{
	NW_CLASS(NewWorld::Graphics, EditorDraw)

		// Sub Classes
	public:
		class LocalPainter : public Object
		{
			NW_CLASS(NewWorld::Graphics, EditorDraw)

			// Members
		private:
			RawPointer<Editor::EditorWindow> m_Window;

			// Getters
		public:
			RawPointer<Editor::EditorWindow> GetWindow() const { return m_Window; }

			// Actions
		public:
			
		};

		// Actions Local
	public:
		static void DrawRectangle(LocalPainter& localPainter, int x, int y, uint width, uint height, const Graphics::Color& color);

		// Actions Global
	public: // TODO: private
		static void DrawRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color);

		// Utilities
	private:
		static Vector4 GetCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y);

		static void AddCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y);
	};
}