#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/Component.h"

namespace NewWorld::Editor::Components
{
	class ComponentContainer : public Component
	{
	NW_CLASS(NewWorld::Editor::Components, ComponentContainer)

		// Members
	private:
		DynamicArray<SharedPointer<Component>> m_Components;

	protected:
		ComponentContainer(float x, float y, float width, float height)
			: Component(x, y, width, height)
		{

		}

		// Override
	public:
		virtual void Destroy() override
		{
			RemoveComponents();

			Component::Destroy();
		}

		virtual void Update() override;

		// Virtual functions
	public:
		virtual void ComponentAdded(SharedPointer<Component> component) { }

		virtual void ComponentRemoved(SharedPointer<Component> component) { }

		virtual void ComponentsRemoved(DynamicArray<SharedPointer<Component>>& components) { }

		// Getters
	public:
		inline DynamicArray<SharedPointer<Component>>& GetComponents() { return m_Components; }

		// Actions
	public:
		void AddComponent(SharedPointer<Component> component)
		{
			m_Components.push_back(component);
			component->SetWindow(GetWindow());

			component->Create();

			ComponentAdded(component);
		}

		void RemoveComponent(SizeT index)
		{
			ComponentRemoved(m_Components[index]);

			m_Components[index]->Destroy();

			m_Components.erase(m_Components.begin() + index);
		}

		void RemoveComponents()
		{
			if (!m_Components.empty())
			{
				ComponentsRemoved(m_Components);

				DynamicArray<SharedPointer<Component>>::iterator iter = m_Components.begin();
				++iter;
				while (iter != m_Components.end())
				{
					Component& component = *(*iter);

					component.Destroy();

					++iter;
				}

				m_Components.clear();
			}
		}
	};
}