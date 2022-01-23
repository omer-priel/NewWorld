#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Component.h"

namespace NewWorld::Editor
{
	class ComponentContainer : public Component
	{
	NW_CLASS(NewWorld::Editor, ComponentContainer)

		// Members
	private:
		DynamicArray<SharedPointer<Component>> m_Components;

	protected:
		ComponentContainer(uint x, uint y, uint width, uint height)
			: Component(x, y, width, height)
		{

		}

	public:
		virtual ~ComponentContainer()
		{
			RemoveComponents();
		}

		// Override
	public:
		virtual void Update() override
		{
			for (SharedPointer<Component>& component : m_Components)
			{
				component->Update();
			}
		}

		// Pure virtual functions
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

			ComponentAdded(component);
		}

		void RemoveComponent(SizeT index)
		{
			ComponentRemoved(m_Components[index]);

			m_Components.erase(m_Components.begin() + index);
		}

		void RemoveComponents()
		{
			if (!m_Components.empty())
			{
				ComponentsRemoved(m_Components);

				m_Components.clear();
			}
		}

		// Override Events
	public:
		virtual void Click(const Events::ClickEvent& e) override
		{
			Component::Click(e);

			if (!m_Components.empty())
			{
				DynamicArray<SharedPointer<Component>>::iterator iter = m_Components.end();
				--iter;
				while (iter != m_Components.begin())
				{
					Component& component = *(*iter);
					if (component.IsIn(e.GetX(), e.GetY()))
					{
						component.Click(e);
						return;
					}

					--iter;
				}
			}
		}
	};
}