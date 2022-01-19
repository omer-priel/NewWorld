#include "nwpch.h"
#include "Panel.h"

#include "NewWorld/Graphics/EditorDraw.h"

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
		Graphics::EditorDraw::DrawRectangle(GetWindow(), m_X, m_Y, m_Width, m_Height, m_BackgroundColor);

		ComponentContainer::Update();
	}

	void Panel::ComponentAdded(SharedPointer<Component> component)
	{

	}

	void Panel::ComponentsRemoved(DynamicArray<SharedPointer<Component>>& components)
	{

	}
}