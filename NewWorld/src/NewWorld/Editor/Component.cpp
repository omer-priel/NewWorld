#include "nwpch.h"
#include "Component.h"

#include "NewWorld/Editor/EditorWindow.h"

namespace NewWorld::Editor
{
	// Events
	void Component::Create()
	{
		m_CreateHandler(*this);
	}

	void Component::Destroy()
	{
		m_DestroyHandler(*this);
	}
	
	void Component::Click()
	{
		m_ClickHandler(*this);
	}

	void Component::MouseKeyPressed(Input::Key key, uint xPos, uint yPos)
	{
		m_MouseKeyPressedHandler(*this, key, xPos, yPos);
	}

	void Component::MouseKeyReleased(Input::Key key, uint xPos, uint yPos)
	{
		NW_DEBUG(NW_LOGGER_CORE, "{} {}", xPos, yPos);
		m_MouseKeyReleasedHandler(*this, key, xPos, yPos);
	}

	void Component::MouseHover(uint xPos, uint yPos)
	{

	}

	void Component::MouseScrolled()
	{

	}
}