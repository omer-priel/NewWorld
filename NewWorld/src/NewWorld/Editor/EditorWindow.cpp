#include "nwpch.h"
#include "EditorWindow.h"

#include "NewWorld/Editor/Graphics2D/LocalPainter.h"
#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor
{
	EditorWindow::EditorWindow(SizeT m_WindowID, const String& title, uint width, uint height)
		: Window(title, width, height), m_WindowID(m_WindowID), m_MainPanel(0, 0, (float)width, (float)height),
		m_SelectedComponent(&m_MainPanel)
	{
		m_MainPanel.SetWindow(this);

		Matrix4 proj = Math::Projection::OrthographicMatrix(0.0f, (float)width, 0.0f, (float)height);
		Matrix4 view = glm::translate(Matrix4(1.0f), Vector3(0, 0, 0));;
		m_ProjectionMatrix = proj * view;
	}

	void EditorWindow::Create()
	{
		Window::Create();

		Graphics2D::EditorDraw::InitializeWindow(this);
	}

	void EditorWindow::Close()
	{
		m_MainPanel.Destroy();
		
		Window::Close();
	}

	void EditorWindow::ChangeSelectedComponent(RawPointer<Components::IComponent> component)
	{
		m_SelectedComponent->Leave();
		m_SelectedComponent = component;
		component->Enter();
	}

	void EditorWindow::Update()
	{
		Window::Update();

		Graphics2D::LocalPainter::ChangeWindow(this);

		m_MainPanel.Update();
	}

	void EditorWindow::MouseKeyPressed(Input::Key key, float xPos, float yPos)
	{
		m_MainPanel.MouseKeyPressed(key, xPos, yPos);
	}

	void EditorWindow::MouseKeyReleased(Input::Key key, float xPos, float yPos)
	{
		m_MainPanel.MouseKeyReleased(key, xPos, yPos);
	}

	void EditorWindow::MouseHover(float xPos, float yPos)
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