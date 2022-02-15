#include "nwpch.h"
#include "EditorWindow.h"

namespace NewWorld::Editor
{
	void EditorWindow::Close()
	{
		m_MainPanel.Destroy();
		
		Window::Close();
	}

	void EditorWindow::Update()
	{
		Window::Update();

		m_MainPanel.Update();
	}

	void EditorWindow::Click(const Events::ClickEvent& e)
	{
		m_MainPanel.Click(e);
	}
}