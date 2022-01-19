#include "nwpch.h"
#include "EditorDraw.h"

#include <GLFW/glfw3.h>

namespace NewWorld::Graphics
{
	void EditorDraw::DrawRectangle(uint x, uint y, uint width, uint height, const Graphics::Color& color)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//glClearColor(color.r, color.g, color.b, 1);

		glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex2f(-0.5f, -0.5f);    // x, y
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();
	}

}