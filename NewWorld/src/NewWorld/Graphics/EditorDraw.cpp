#include "nwpch.h"
#include "EditorDraw.h"

#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace NewWorld::Graphics
{
	Vector4 GetCoordinate(RawPointer<Editor::EditorWindow> window, float x, float y)
	{
		Matrix4 proj = window->GetProjectionMatrix();

		return Vector4(x - window->GetWidth() / 2, y - window->GetHeight() / 2, 0, 1) * proj;
	}

	void AddCoordinate2(RawPointer<Editor::EditorWindow> window, float x, float y)
	{
		Vector4 coordinate = GetCoordinate(window, x, y);
		glVertex2f(coordinate.x, coordinate.y);
	}

	void EditorDraw::DrawRectangle(RawPointer<Editor::EditorWindow> window, uint x, uint y, uint width, uint height, const Graphics::Color& color)
	{
		NW_INFO(NW_LOGGER_CORE, color);
		Matrix4& proj = window->GetProjectionMatrix();

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		glColor3f(color.r, color.g, color.b);
		AddCoordinate2(window, x, y);
		AddCoordinate2(window, width, y);
		AddCoordinate2(window, width, y + height);
		AddCoordinate2(window, x, y + height);
		glEnd();
	}

	void EditorDraw::AddCoordinate(Matrix4& proj, uint x, uint y)
	{
		//Matrix4 proj2 = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);
		//Matrix4 proj2 = Math::Projection::OrthographicMatrix(0, 0, 1280, 720);
		//Matrix4 proj2 = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, 0.1f, 100.0f);

		Matrix4 proj2 = glm::ortho(-2.0f, 2.0f, 1.5f, 1.5f, -1.0f, 1.0f);

		Vector4 coordinate = Vector4(x, y, 0, 1) * proj2;
		glVertex2f(coordinate.x, coordinate.y);
	}
}