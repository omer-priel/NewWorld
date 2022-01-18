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

	public:
		virtual ~ComponentContainer()
		{
			RemoveComponents();
		}

		// Pure virtual functions
	public:
		virtual void ComponentAdded(Component& component) = 0;

		virtual void ComponentsRemoved(DynamicArray<Component>& components) = 0;

		// Getters
	public:
		inline DynamicArray<Component>& GetComponents() { return m_Components; }

		// Actions
	public:
		void AddComponent(Component& component)
		{
			m_Components.push_back(component);
			
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