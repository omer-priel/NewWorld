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
		component->Create();
	}

	void Panel::ComponentRemoved(SharedPointer<Component> component)
	{

	}

	void Panel::ComponentsRemoved(DynamicArray<SharedPointer<Component>>& components)
	{

	}

	void Panel::Click(const Events::ClickEvent& e)
	{
		ComponentContainer::Click(e);

		auto components = this->GetComponents();

		if (!components.empty())
		{
			DynamicArray<SharedPointer<Component>>::iterator iter = components.begin();
			++iter;
			while (iter != components.end())
			{
				Component& component = *(*iter);
				if (component.IsIn(e.GetX(), e.GetY()))
				{
					component.Click(e);
					return;
				}

				++iter;
			}
		}
	}
}