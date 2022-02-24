#include "nwpch.h"
#include "EditorDraw.h"

#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace NewWorld::Graphics
{
	// Local
	void EditorDraw::DrawRectangle(int x, int y, uint width, uint height, const Graphics::Color& color)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawRectangle(LocalPainter::GetWindow(), x, y, width, height, color);
	}

	void EditorDraw::DrawLine(int x1, int y1, int x2, int y2, const Graphics::Color& color)
	{
		x1 += LocalPainter::GetX();
		y1 += LocalPainter::GetY();
		x2 += LocalPainter::GetX();
		y2 += LocalPainter::GetY();

		DrawLine(LocalPainter::GetWindow(), x1, y1, x2, y2, color);
	}

	// Global
	void EditorDraw::DrawRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color)
	{
		glBegin(GL_QUADS);
		glColor3f(color.r, color.g, color.b);
		AddCoordinate(window, x, y);
		AddCoordinate(window, x + width, y);
		AddCoordinate(window, x + width, y + height);
		AddCoordinate(window, x, y + height);
		glEnd();
	}

	void EditorDraw::DrawLine(RawPointer<Editor::EditorWindow> window, int x1, int y1, int x2, int y2, const Graphics::Color& color)
	{
		glBegin(GL_LINES);
		glColor3f(color.r, color.g, color.b);
		AddCoordinate(window, x1, y1);
		AddCoordinate(window, x2, y2);
		glEnd();
	}

	// Utilities
	Vector4 EditorDraw::GetCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y)
	{
		Matrix4 proj = window->GetProjectionMatrix();

		return Vector4(x - window->GetWidth() / 2, y - window->GetHeight() / 2, 0, 1) * proj;
	}

	void EditorDraw::AddCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y)
	{
		Vector4 coordinate = GetCoordinate(window, x, y);
		glVertex2f(coordinate.x, coordinate.y);
	}
}