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

	void EditorDraw::DrawOutlineRectangle(int x, int y, 
		uint width, uint height, const Graphics::Color& color, uint lineWidth)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawOutlineRectangle(LocalPainter::GetWindow(), x, y, width, height, color, lineWidth);
	}

	void EditorDraw::DrawEllipse(int x, int y, uint radiusX, uint radiusY, const Graphics::Color& color)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipse(LocalPainter::GetWindow(), x, y, radiusX, radiusY, color);
	}

	void EditorDraw::DrawOutlineEllipse(int x, int y,
		uint radiusX, uint radiusY, const Graphics::Color& color, uint lineWidth)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawOutlineEllipse(LocalPainter::GetWindow(), x, y, radiusX, radiusY, color, lineWidth);
	}

	void EditorDraw::DrawOval(int x, int y, uint radius, const Graphics::Color& color)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipse(LocalPainter::GetWindow(), x, y, radius, radius, color);
	}

	void EditorDraw::DrawOutlineOval(int x, int y, uint radius, const Graphics::Color& color, uint lineWidth)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawOutlineEllipse(LocalPainter::GetWindow(), x, y, radius, radius, color, lineWidth);
	}

	// Global
	void EditorDraw::DrawLine(RawPointer<Editor::EditorWindow> window, 
		int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth)
	{
		NW_ASSERT(lineWidth <= 10, "Line Width cant be over 10.");

		Vector4 v1 = GetCoordinate(window, x1, y1);
		Vector4 v2 = GetCoordinate(window, x2, y2);

		GLfloat lineVertices[] = {
			v1.x, v1.y, 0,
			v2.x, v2.y, 0
		};

		BeforeDraw();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(lineWidth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, lineVertices);
		glColor3f(color.r, color.g, color.b);
		glDrawArrays(GL_LINES, 0, 2);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_LINE_SMOOTH);

		AfterDraw();
	}

	void EditorDraw::DrawFillRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, 
		uint width, uint height, const Graphics::Color& color)
	{
		Vector4 v1 = GetCoordinate(window, x, y);
		Vector4 v2 = GetCoordinate(window, x + width, y);
		Vector4 v3 = GetCoordinate(window, x, y + height);
		Vector4 v4 = GetCoordinate(window, x + width, y + height);

		GLfloat vertices[] = {
			v1.x, v1.y, 0,
			v2.x, v2.y, 0,
			v4.x, v4.y, 0,

			v1.x, v1.y, 0,
			v3.x, v3.y, 0,
			v4.x, v4.y, 0
		};

		BeforeDraw();

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, vertices);
		glColor4f(color.r, color.g, color.b, color.a);
		glDrawArrays(GL_TRIANGLES, 0, 3 * 2);
		glDisableClientState(GL_VERTEX_ARRAY);

		AfterDraw();

	}

	void EditorDraw::DrawOutlineRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, 
		uint width, uint height, const Graphics::Color& color, uint lineWidth)
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

		BeforeDraw();

		glLineWidth(lineWidth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(3, GL_FLOAT, 0, lineVertices);
		glColor4f(color.r, color.g, color.b, color.a);
		glDrawArrays(GL_LINES, 0, 2*4);
		glDisableClientState(GL_VERTEX_ARRAY);

		AfterDraw();
	}

	void EditorDraw::DrawEllipse(RawPointer<Editor::EditorWindow> window, int x, int y, 
		uint radiusX, uint radiusY, const Graphics::Color& color)
	{
		BeforeDraw();



		AfterDraw();
	}

	void EditorDraw::DrawOutlineEllipse(RawPointer<Editor::EditorWindow> window, int x, int y, 
		uint radiusX, uint radiusY, const Graphics::Color& color, uint lineWidth)
	{

	}

	// Utilities
	void EditorDraw::BeforeDraw()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void EditorDraw::AfterDraw()
	{
		glDisable(GL_BLEND);
	}

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