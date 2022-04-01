#include "nwpch.h"
#include "ComponentContainer.h"

#include "NewWorld/Editor/Graphics2D/LocalPainter.h"

namespace NewWorld::Editor::Components
{
	// Override
	void ComponentContainer::Update()
	{
		Graphics2D::LocalPainter::Enter(*this);

		for (SharedPointer<IComponent>& component : m_Components)
		{
			component->Update();
		}

		Graphics2D::LocalPainter::Leave(*this);

		Component::Update();
	}

	// Actions
	void ComponentContainer::AddComponent(SharedPointer<IComponent> component)
	{
		m_Components.push_back(component);
		component->SetWindow(GetWindow());

		component->Create();

		ComponentAdded(component);
	}

	void ComponentContainer::RemoveComponent(SizeT index)
	{
		ComponentRemoved(m_Components[index]);

		m_Components[index]->Destroy();

		m_Components.erase(m_Components.begin() + index);
	}

	void ComponentContainer::RemoveComponents()
	{
		if (!m_Components.empty())
		{
			ComponentsRemoved(m_Components);

			DynamicArray<SharedPointer<IComponent>>::iterator iter = m_Components.begin();
			++iter;
			while (iter != m_Components.end())
			{
				IComponent& component = *(*iter);

				component.Destroy();

				++iter;
			}

			m_Components.clear();
		}
	}
}