#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Editor/Graphics2D/LocalPainter.h"
#include "NewWorld/Editor/EditorWindow.h"

namespace NewWorld::Editor::Graphics2D
{
	using Color = Graphics::Color;

	// This is static class
	class EditorDraw : public Object
	{
	NW_CLASS(NewWorld::Editor::Graphics2D, EditorDraw)

		// Initialize Window
	public:
		static void InitializeWindow(RawPointer<EditorWindow> window);

		// Actions Local
	public:
		static void DrawLine(float x1, float y1, float x2, float y2, const Color& color, float lineWidth = 1.0f);

		static void DrawRectangle(float x, float y, float width, float height, const Color& color);
		static void DrawOutlineRectangle(float x, float y, float width, float height, const Color& color, float lineWidth = 1.0f);
		
		static void DrawEllipseSlice(float x, float y, float radiusX, float radiusY, float angleStart, float angleLength, const Color& color, uint verticesCount = 42);
		static void DrawArc(float x, float y, float radiusX, float radiusY, float startAngle, float angleLength, const Color& color, float lineWidth = 1.0f, uint verticesCount = 42);

		static void DrawEllipse(float x, float y, float radiusX, float radiusY, const Color& color, uint verticesCount = 42);
		static void DrawOutlineEllipse(float x, float y, float radiusX, float radiusY, const Color& color, float lineWidth = 1.0f, uint verticesCount = 42);

		static void DrawOval(float x, float y, float radius, const Color& color, uint verticesCount = 42);
		static void DrawOutlineOval(float x, float y, float radius, const Color& color, float lineWidth = 1.0f, uint verticesCount = 42);

		static void DrawTexture(float x, float y, float width, float height, Assets::Texture& texture);
		static void DrawTexture(float x, float y, float width, float height, Assets::Texture& texture,
		uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight);

		static void DrawTemplateTexture(float x, float y, float width, float height, Assets::Texture& texture,
			const Color& color);
		static void DrawTemplateTexture(float x, float y, float width, float height, Assets::Texture& texture,
			const Color& color, uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight);

		static void DrawString(float x, float y, String text,
			const Color& color, uint fontSize, float maxWidth = 0, bool bold = false, bool italic = false);

		// Actions Global
	private:
		static void DrawLine(RawPointer<EditorWindow> window, float x1, float y1, float x2, float y2, const Color& color, float lineWidth);

		static void DrawFillRectangle(RawPointer<EditorWindow> window, float x, float y, float width, float height, const Color& color);
		static void DrawOutlineRectangle(RawPointer<EditorWindow> window, float x, float y, float width, float height, const Color& color, float lineWidth);

		static void DrawEllipseSlice(RawPointer<EditorWindow> window, float x, float y, float radiusX, float radiusY, float angleStart, float angleLength, const Color& color, uint verticesCount = 64);
		static void DrawArc(RawPointer<EditorWindow> window, float x, float y, float radiusX, float radiusY, float angleStart, float angleLength, const Color& color, float lineWidth = 1.0f, uint verticesCount = 64);
		
		static void DrawTexture(RawPointer<EditorWindow> window, float x, float y, float width, float height,
			Assets::Texture& texture, uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight);
		
		static void DrawTemplateTexture(RawPointer<EditorWindow> window, float x, float y, float width, float height,
			Assets::Texture& texture, const Color& color, uint sampleX, uint sampleY, uint sampleWidth, uint sampleHeight);
		
		static void DrawString(RawPointer<EditorWindow> window, float x, float y, String text,
			const Color& color, uint fontSize, float maxWidth, bool bold, bool italic);

		// Utilities
	private:
		static void BeforeDraw(uint* buffer);
		static void AfterDraw(uint* buffer);

		static SharedPointer<Assets::Shader> CreateShader(uint shaderID);
	};
}