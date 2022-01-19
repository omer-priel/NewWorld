#include "nwpch.h"
#include "Panel.h"

// TEMP
#include <GLFW/glfw3.h>

namespace NewWorld::Editor::UI
{
	// Override
	void Panel::Create()
	{

	}

	void Panel::Destroy()
	{

	}

	void Panel::Update()
	{
		glClear(GL_COLOR_BUFFER_BIT);
		//glClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, 1);

		glBegin(GL_QUADS);              // Each set of 4 vertices form a quad
		glColor3f(1.0f, 0.0f, 0.0f); // Red
		glVertex2f(-0.5f, -0.5f);    // x, y
		glVertex2f(0.5f, -0.5f);
		glVertex2f(0.5f, 0.5f);
		glVertex2f(-0.5f, 0.5f);
		glEnd();

		ComponentContainer::Update();
	}

	void Panel::ComponentAdded(Component& component)
	{

	}

	void Panel::ComponentsRemoved(DynamicArray<Component>& components)
	{

	}
}