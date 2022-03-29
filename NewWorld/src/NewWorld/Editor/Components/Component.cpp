#include "nwpch.h"
#include "Component.h"

#include "NewWorld/Editor/EditorWindow.h"
#include "NewWorld/Editor/Components/ComponentContainer.h"

namespace NewWorld::Editor::Components
{
	// Events
	void Component::Create()
	{
		m_CreateHandler(*this);
	}

	void Component::Destroy()
	{
		m_DestroyHandler(*this);

		if (m_Window->IsSelectedComponent(this)) {
			m_Window->ClearSelectedComponent();
		}
	}
	
	void Component::Enter()
	{
		m_EnterHandler(*this);
	}

	void Component::Leave()
	{
		m_LeaveHandler(*this);
	}

	void Component::MouseKeyPressed(Input::Key key, float xPos, float yPos)
	{
		m_MouseKeyPressedHandler(*this, key, xPos, yPos);
	}

	void Component::MouseKeyReleased(Input::Key key, float xPos, float yPos)
	{
		m_MouseKeyReleasedHandler(*this, key, xPos, yPos);
		if (key == Input::Key::MouseButtonLeft) {
			Click();
		}
	}

	void Component::MouseHover(float xPos, float yPos)
	{
		m_MouseHoverHandler(*this, xPos, yPos);
	}

	void Component::MouseScrolled(uint y)
	{
		m_MouseScrolledHandler(*this, y);
	}

	void Component::KeyPressed(Input::Key key)
	{
		m_KeyPressedHandler(*this, key);
	}

	void Component::KeyReleased(Input::Key key)
	{
		m_KeyReleasedHandler(*this, key);

		if (key == Input::Key::Enter)
		{
			Click();
		}
	}

	void Component::Click()
	{
		if (!(m_Window->IsSelectedComponent(this))) {
			m_Window->ChangeSelectedComponent(this);
		}

		m_ClickHandler(*this);
	}
}