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
	
	void Component::Click(Input::Key key, uint xPos, uint yPos)
	{
		NW_DEBUG(NW_LOGGER_CORE, "{} {}", xPos, yPos);
		m_ClickHandler(*this);
	}
}