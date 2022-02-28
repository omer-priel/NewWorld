#include "nwpch.h"
#include "EditorDraw.h"

#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace NewWorld::Graphics
{
	// Local
	void EditorDraw::DrawLine(int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth)
	{
		x1 += LocalPainter::GetX();
		y1 += LocalPainter::GetY();
		x2 += LocalPainter::GetX();
		y2 += LocalPainter::GetY();

		DrawLine(LocalPainter::GetWindow(), x1, y1, x2, y2, color, lineWidth);
	}

	void EditorDraw::DrawRectangle(int x, int y, uint width, uint height, const Graphics::Color& color)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawFillRectangle(LocalPainter::GetWindow(), x, y, width, height, color);
	}

	void EditorDraw::DrawOutlineRectangle(int x, int y, uint width, uint height, const Graphics::Color& color, uint lineWidth)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawOutlineRectangle(LocalPainter::GetWindow(), x, y, width, height, color, lineWidth);
	}

	// Global
	void EditorDraw::DrawLine(RawPointer<Editor::EditorWindow> window, int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth)
	{
		NW_ASSERT(lineWidth <= 10, "Line Width cant be over 10.");

		Vector4 v1 = GetCoordinate(window, x1, y1);
		Vector4 v2 = GetCoordinate(window, x2, y2);

		GLfloat lineVertices[] = {
			v1.x, v1.y, 0,
			v2.x, v2.y, 0
		};

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(lineWidth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, lineVertices);
		glColor3f(color.r, color.g, color.b);
		glDrawArrays(GL_LINES, 0, 2);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_LINE_SMOOTH);
	}

	void EditorDraw::DrawFillRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color)
	{
		glBegin(GL_QUADS);
		glColor3f(color.r, color.g, color.b);
		AddCoordinate(window, x, y);
		AddCoordinate(window, x + width, y);
		AddCoordinate(window, x + width, y + height);
		AddCoordinate(window, x, y + height);
		glEnd();
	}

	void EditorDraw::DrawOutlineRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, uint width, uint height, const Graphics::Color& color, uint lineWidth)
	{
		NW_ASSERT(lineWidth <= 10, "Line Width cant be over 10.");

		uint halfLineWidth = lineWidth / 2;

		Vector4 vUp1 = GetCoordinate(window, x, y + halfLineWidth);
		Vector4 vUp2 = GetCoordinate(window, x + width, y + halfLineWidth);

		Vector4 vDown1 = GetCoordinate(window, x, y + height - halfLineWidth);
		Vector4 vDown2 = GetCoordinate(window, x + width, y + height - halfLineWidth);

		Vector4 vLeft1 = GetCoordinate(window, x + halfLineWidth, y + lineWidth);
		Vector4 vLeft2 = GetCoordinate(window, x + halfLineWidth, y + height - lineWidth);

		Vector4 vRight1 = GetCoordinate(window, x + width - halfLineWidth, y + lineWidth);
		Vector4 vRight2 = GetCoordinate(window, x + width - halfLineWidth, y + height - lineWidth);

		GLfloat lineVertices[] = {
			vUp1.x, vUp1.y, 0,
			vUp2.x, vUp2.y, 0,
			
			vDown1.x, vDown1.y, 0,
			vDown2.x, vDown2.y, 0,
			
			vLeft1.x, vLeft1.y, 0,
			vLeft2.x, vLeft2.y, 0,

			vRight1.x, vRight1.y, 0,
			vRight2.x, vRight2.y, 0
		};

		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_SRC_COLOR);
		glLineWidth(lineWidth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, lineVertices);
		glColor4f(color.r, color.g, color.b, color.a);
		glDrawArrays(GL_LINES, 0, 2*4);
		glDisableClientState(GL_VERTEX_ARRAY);
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