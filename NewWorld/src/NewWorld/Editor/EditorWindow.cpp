#include "nwpch.h"
#include "EditorWindow.h"

namespace NewWorld::Editor
{
	void EditorWindow::Close()
	{
		m_MainPanel.Destroy();
		
		Window::Close();
	}

	void EditorWindow::ChangeSelectedComponent(RawPointer<Component> component)
	{
		m_SelectedComponent->Leave();
		m_SelectedComponent = component;
		component->Enter();
	}

	void EditorWindow::Update()
	{
		Window::Update();

		m_MainPanel.Update();
	}

	void EditorWindow::MouseKeyPressed(Input::Key key, uint xPos, uint yPos)
	{
		m_MainPanel.MouseKeyPressed(key, xPos, yPos);
	}

	void EditorWindow::MouseKeyReleased(Input::Key key, uint xPos, uint yPos)
	{
		m_MainPanel.MouseKeyReleased(key, xPos, yPos);
	}

	void EditorWindow::MouseHover(uint xPos, uint yPos)
	{
		m_MainPanel.MouseHover(xPos, yPos);
	}

	void EditorWindow::MouseScrolled(uint y)
	{
		m_SelectedComponent->MouseScrolled(y);
	}

	void EditorWindow::KeyPressed(Input::Key key)
	{
		m_SelectedComponent->KeyPressed(key);
	}

	void EditorWindow::KeyReleased(Input::Key key)
	{
		m_SelectedComponent->KeyReleased(key);
	}
}