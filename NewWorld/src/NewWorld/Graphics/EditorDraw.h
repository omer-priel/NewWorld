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

		// Initialize Window
	public:
		static void InitializeWindow(RawPointer<Editor::EditorWindow> window);

		// Actions Local
	public:
		static void DrawLine(int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth = 1);

		static void DrawRectangle(int x, int y, uint width, uint height, const Graphics::Color& color);
		static void DrawOutlineRectangle(int x, int y, uint width, uint height, const Graphics::Color& color, uint lineWidth = 1);
		
		static void DrawEllipseSlice(int x, int y, uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint verticesCount = 42);
		static void DrawArc(int x, int y, uint radiusX, uint radiusY, float startAngle, float angleLength, const Graphics::Color& color, uint lineWidth = 1, uint verticesCount = 42);

		static void DrawEllipse(int x, int y, uint radiusX, uint radiusY, const Graphics::Color& color, uint verticesCount = 42);
		static void DrawOutlineEllipse(int x, int y, uint radiusX, uint radiusY, const Graphics::Color& color, uint lineWidth = 1, uint verticesCount = 42);

		static void DrawOval(int x, int y, uint radius, const Graphics::Color& color, uint verticesCount = 42);
		static void DrawOutlineOval(int x, int y, uint radius, const Graphics::Color& color, uint lineWidth = 1, uint verticesCount = 42);

		static void DrawTexture(int x, int y, uint width, uint height, Editor::Assets::Texture& texture);
		static void DrawTexture(int x, int y, uint width, uint height, Editor::Assets::Texture& texture,
		uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight);

		static void DrawTemplateTexture(int x, int y, uint width, uint height, Editor::Assets::Texture& texture,
			const Graphics::Color& color);
		static void DrawTemplateTexture(int x, int y, uint width, uint height, Editor::Assets::Texture& texture,
			const Graphics::Color& color, uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight);

		static void DrawString(int x, int y, String text,
			const Graphics::Color& color, uint fontSize, bool bold = false, bool italic = false);

		// Actions Global
	private:
		static void DrawLine(RawPointer<Editor::EditorWindow> window, int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth);

		static void DrawFillRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color);
		static void DrawOutlineRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color, uint lineWidth);

		static void DrawEllipseSlice(RawPointer<Editor::EditorWindow> window, int x, int y, uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint verticesCount = 64);
		static void DrawArc(RawPointer<Editor::EditorWindow> window, int x, int y, uint radiusX, uint radiusY, float angleStart, float angleLength, const Graphics::Color& color, uint lineWidth = 1, uint verticesCount = 64);
		
		static void DrawTexture(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height,
			Editor::Assets::Texture& texture, uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight);
		
		static void DrawTemplateTexture(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height,
			Editor::Assets::Texture& texture, const Graphics::Color& color, uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight);
		
		static void DrawString(RawPointer<Editor::EditorWindow> window, int x, int y, String text,
			const Graphics::Color& color, uint fontSize, bool bold, bool italic);

		// Utilities
	private:
		static void BeforeDraw();
		static SharedPointer<Editor::Assets::Shader> CreateShader(uint shaderID);
		static void AfterDraw();
	};
}