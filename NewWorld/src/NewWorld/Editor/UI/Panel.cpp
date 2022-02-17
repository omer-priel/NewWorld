#include "nwpch.h"
#include "Panel.h"

#include "NewWorld/Graphics/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	// Override
	void Panel::Create()
	{
		ComponentContainer::Create();
	}

	void Panel::Destroy()
	{
		ComponentContainer::Destroy();
	}

	void Panel::Update()
	{
		Graphics::EditorDraw::DrawRectangle(GetWindow(), m_X, m_Y, m_Width, m_Height, m_BackgroundColor);

		ComponentContainer::Update();
	}

	void Panel::ComponentAdded(SharedPointer<Component> component)
	{
		ComponentContainer::ComponentAdded(component);
	}

	void Panel::ComponentRemoved(SharedPointer<Component> component)
	{
		ComponentContainer::ComponentRemoved(component);
	}

	void Panel::ComponentsRemoved(DynamicArray<SharedPointer<Component>>& components)
	{
		ComponentContainer::ComponentsRemoved(components);
	}

	void Panel::Click(Input::Key key, uint xPos, uint yPos)
	{
		ComponentContainer::Click(key, xPos, yPos);

		auto components = this->GetComponents();

		if (!components.empty())
		{
			DynamicArray<SharedPointer<Component>>::iterator iter = components.begin();
			++iter;
			while (iter != components.end())
			{
				Component& component = *(*iter);
				if (component.IsIn(xPos, yPos))
				{
					component.Click(key, xPos, yPos);
					return;
				}

				++iter;
			}
		}
	}
}