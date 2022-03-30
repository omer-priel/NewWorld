#include "nwpch.h"
#include "Panel.h"

#include "NewWorld/Editor/Graphics2D/EditorDraw.h"

namespace NewWorld::Editor::UI
{
	using namespace NewWorld::Editor::Components;

	// Override
	void Panel::Update()
	{
		Graphics2D::EditorDraw::DrawRectangle(m_X, m_Y, m_Width, m_Height, m_BackgroundColor);

		Component::Update();
	}

	void Panel::Destroy()
	{
		IContainerComponent::Destroy();
		Component::Destroy();
	}

	void Panel::MouseKeyPressed(Input::Key key, float xPos, float yPos)
	{
		auto& components = this->GetSubComponents();

		DynamicArray<SharedPointer<IComponent>>::iterator iter = components.end();
		while (iter != components.begin())
		{
			iter--;
			IComponent& component = *(*iter);
			
			if (component.IsIn(xPos, yPos))
			{
				component.MouseKeyPressed(key, xPos - component.GetX(), yPos - component.GetY());
				return;
			}
		}

		Component::Update();
	}

	void Panel::MouseKeyReleased(Input::Key key, float xPos, float yPos)
	{
		auto& components = this->GetSubComponents();

		DynamicArray<SharedPointer<IComponent>>::iterator iter = components.end();
		while (iter != components.begin())
		{
			iter--;
			IComponent& component = *(*iter);
			
			if (component.IsIn(xPos, yPos))
			{
				component.MouseKeyReleased(key, xPos - component.GetX(), yPos - component.GetY());
				return;
			}
		}

		Component::MouseKeyReleased(key, xPos, yPos);
	}

	void Panel::MouseHover(float xPos, float yPos)
	{
		auto& components = this->GetSubComponents();

		DynamicArray<SharedPointer<IComponent>>::iterator iter = components.end();
		while (iter != components.begin())
		{
			iter--;
			IComponent& component = *(*iter);
			
			if (component.IsIn(xPos, yPos))
			{
				component.MouseHover(xPos - component.GetX(), yPos - component.GetY());
				return;
			}
		}

		Component::MouseHover(xPos, yPos);
	}
}