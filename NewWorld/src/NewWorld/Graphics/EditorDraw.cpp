#include "nwpch.h"
#include "EditorDraw.h"

#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

namespace NewWorld::Graphics
{
	void EditorDraw::DrawRectangle(Editor::EditorWindow& window, uint x, uint y, uint width, uint height, const Graphics::Color& color)
	{
		NW_INFO(NW_LOGGER_CORE, color);
		Matrix4& proj = window.GetProjectionMatrix();

		glClear(GL_COLOR_BUFFER_BIT);
		glBegin(GL_QUADS);
		glColor3f(color.r, color.g, color.b);
		AddCoordinate(proj, x, y);
		AddCoordinate(proj, x + width, y);
		AddCoordinate(proj, x + width, y + height);
		AddCoordinate(proj, x, y + height);
		glEnd();
	}

	void EditorDraw::AddCoordinate(Matrix4& proj, uint x, uint y)
	{
		Matrix4 proj2 = glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f, -1.0f, 1.0f);

		Vector4 coordinate = Vector4(x, y, 0, 1) * proj;
		glVertex2f(coordinate.x, coordinate.y);
	}
}