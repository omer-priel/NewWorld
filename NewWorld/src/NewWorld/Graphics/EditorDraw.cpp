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

	void EditorDraw::DrawEllipseSlice(int x, int y, uint radiusX, uint radiusY, float angleStart, float angleEnd, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radiusX, radiusY, angleStart, angleEnd, color, verticesCount);
	}
	
	void EditorDraw::DrawArc(int x, int y, uint radiusX, uint radiusY, float angleStart, float angleEnd, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radiusX, radiusY, angleStart, angleEnd, color, lineWidth, verticesCount);
	}

	void EditorDraw::DrawEllipse(int x, int y, uint radiusX, uint radiusY, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radiusX, radiusY, 0, NewWorld::Math::PI_2, color, verticesCount);
	}

	void EditorDraw::DrawOutlineEllipse(int x, int y,
		uint radiusX, uint radiusY, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radiusX, radiusY, 0, NewWorld::Math::PI_2, color, lineWidth, verticesCount);
	}

	void EditorDraw::DrawOval(int x, int y, uint radius, const Graphics::Color& color, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawEllipseSlice(LocalPainter::GetWindow(), x, y, radius, radius, 0, NewWorld::Math::PI_2, color, verticesCount);
	}

	void EditorDraw::DrawOutlineOval(int x, int y, uint radius, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		x += LocalPainter::GetX();
		y += LocalPainter::GetY();

		DrawArc(LocalPainter::GetWindow(), x, y, radius, radius, 0, NewWorld::Math::PI_2, color, lineWidth, verticesCount);
	}

	// Global
	void EditorDraw::DrawLine(RawPointer<Editor::EditorWindow> window, 
		int x1, int y1, int x2, int y2, const Graphics::Color& color, uint lineWidth)
	{
		NW_ASSERT(lineWidth <= 10, "Line Width cant be over 10.");

		Vector2 v1 = GetCoordinate(window, x1, y1);
		Vector2 v2 = GetCoordinate(window, x2, y2);

		GLfloat lineVertices[] = {
			v1.x, v1.y,
			v2.x, v2.y
		};

		BeforeDraw();

		glEnable(GL_LINE_SMOOTH);
		glLineWidth(lineWidth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, lineVertices);
		glColor4f(color.r, color.g, color.b, color.a);
		glDrawArrays(GL_LINES, 0, 2);
		glDisableClientState(GL_VERTEX_ARRAY);
		glDisable(GL_LINE_SMOOTH);

		AfterDraw();
	}

	void EditorDraw::DrawFillRectangle(RawPointer<Editor::EditorWindow> window, int x, int y, 
		uint width, uint height, const Graphics::Color& color)
	{
		Vector2 v1 = GetCoordinate(window, x, y);
		Vector2 v2 = GetCoordinate(window, x + width, y);
		Vector2 v3 = GetCoordinate(window, x, y + height);
		Vector2 v4 = GetCoordinate(window, x + width, y + height);

		GLfloat vertices[] = {
			v1.x, v1.y,
			v2.x, v2.y,
			v4.x, v4.y,

			v1.x, v1.y,
			v3.x, v3.y,
			v4.x, v4.y
		};

		BeforeDraw();

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
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

		Vector2 vUp1 = GetCoordinate(window, x, y + halfLineWidth);
		Vector2 vUp2 = GetCoordinate(window, x + width, y + halfLineWidth);

		Vector2 vDown1 = GetCoordinate(window, x, y + height - halfLineWidth);
		Vector2 vDown2 = GetCoordinate(window, x + width, y + height - halfLineWidth);

		Vector2 vLeft1 = GetCoordinate(window, x + halfLineWidth, y + lineWidth);
		Vector2 vLeft2 = GetCoordinate(window, x + halfLineWidth, y + height - lineWidth);

		Vector2 vRight1 = GetCoordinate(window, x + width - halfLineWidth, y + lineWidth);
		Vector2 vRight2 = GetCoordinate(window, x + width - halfLineWidth, y + height - lineWidth);

		GLfloat lineVertices[] = {
			vUp1.x, vUp1.y,
			vUp2.x, vUp2.y,
			
			vDown1.x, vDown1.y,
			vDown2.x, vDown2.y,
			
			vLeft1.x, vLeft1.y,
			vLeft2.x, vLeft2.y,

			vRight1.x, vRight1.y,
			vRight2.x, vRight2.y
		};

		BeforeDraw();

		glLineWidth(lineWidth);
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, lineVertices);
		glColor4f(color.r, color.g, color.b, color.a);
		glDrawArrays(GL_LINES, 0, 2*4);
		glDisableClientState(GL_VERTEX_ARRAY);

		AfterDraw();
	}

	void EditorDraw::DrawEllipseSlice(RawPointer<Editor::EditorWindow> window, int x, int y,
		uint radiusX, uint radiusY, float angleStart, float angleEnd, const Graphics::Color& color, uint verticesCount)
	{
		Vector2 center = GetCoordinate(window, x, y);
		Vector2 diameter(radiusX / (float)window->GetWidth() * 2, radiusY / (float)window->GetHeight() * 2);

		Vector2 prevVertice(center.x, center.y - diameter.y / 2);

		BeforeDraw();

		glColor4f(color.r, color.g, color.b, color.a);

		float angle = angleStart;
		float angleStep = (angleEnd - angleStart) / verticesCount;

		for (uint i = 0; i <= verticesCount; i++)
		{
			glBegin(GL_TRIANGLES);
			glVertex2f(center.x, center.y);
			glVertex2f(prevVertice.x, prevVertice.y);

			prevVertice.x = center.x + diameter.x * sin(angle);
			prevVertice.y = center.y + diameter.y * cos(angle);

			glVertex2f(prevVertice.x, prevVertice.y);

			glEnd();

			angle += angleStep;
		}

		AfterDraw();
	}
	
	void EditorDraw::DrawArc(RawPointer<Editor::EditorWindow> window, int x, int y,
		uint radiusX, uint radiusY, float angleStart, float angleEnd, const Graphics::Color& color, uint lineWidth, uint verticesCount)
	{
		Vector2 center = GetCoordinate(window, x, y);
		Vector2 diameter(radiusX / (float)window->GetWidth() * 2, radiusY / (float)window->GetHeight() * 2);

		BeforeDraw();

		glLineWidth(lineWidth);
		glBegin(GL_LINE_STRIP);
		glColor4f(color.r, color.g, color.b, color.a);

		float angle = angleStart;
		float angleStep = (angleEnd - angleStart) / verticesCount;

		for (uint i = 0; i <= verticesCount; i++)
		{
			float pointX = center.x + diameter.x * sin(angle);
			float pointY = center.y + diameter.y * cos(angle);

			glVertex2f(pointX, pointY);

			angle += angleStep;
		}

		glEnd();

		AfterDraw();
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

	Vector2 EditorDraw::GetCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y)
	{
		Matrix4 proj = window->GetProjectionMatrix();
		Vector4 vec4 = Vector4(x - window->GetWidth() / 2, y - window->GetHeight() / 2, 0, 1) * proj;
		return vec4;
	}

	void EditorDraw::AddCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y)
	{
		Vector2 coordinate = GetCoordinate(window, x, y);
		glVertex2f(coordinate.x, coordinate.y);
	}
}