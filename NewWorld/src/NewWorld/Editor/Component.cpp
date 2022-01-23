#include "nwpch.h"
#include "Component.h"

#include "NewWorld/Editor/EditorWindow.h"

namespace NewWorld::Editor
{
	// Events
	void Component::Click(const Events::ClickEvent& e)
	{
		m_ClickHandler(*this, e);
	}
}