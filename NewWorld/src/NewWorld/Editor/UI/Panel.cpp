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

	void Panel::OnUpdate()
	{
		glClearColor(m_BackgroundColor.r, m_BackgroundColor.g, m_BackgroundColor.b, 1);
		glClear(GL_COLOR_BUFFER_BIT);
	}

	void Panel::ComponentAdded(Component& component)
	{

	}

	void Panel::ComponentsRemoved(DynamicArray<Component>& components)
	{

	}
}