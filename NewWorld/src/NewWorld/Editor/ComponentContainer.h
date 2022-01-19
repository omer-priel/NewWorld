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
		DynamicArray<Component> m_Components;

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
			for (Component& component : m_Components)
			{
				component.Update();
			}
		}

		// Pure virtual functions
	public:
		virtual void ComponentAdded(Component& component) { }

		virtual void ComponentsRemoved(DynamicArray<Component>& components) { }

		// Getters
	public:
		inline DynamicArray<Component>& GetComponents() { return m_Components; }

		// Actions
	public:
		void AddComponent(Component& component)
		{
			m_Components.push_back(component);
			component.SetWindow(GetWindow());

			ComponentAdded(component);
		}

		void RemoveComponents()
		{
			if (!m_Components.empty())
			{
				ComponentsRemoved(m_Components);

				m_Components.clear();
			}
		}
	};
}