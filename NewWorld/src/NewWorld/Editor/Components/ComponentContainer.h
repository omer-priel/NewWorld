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
		DynamicArray<SharedPointer<IComponent>> m_Components;

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
		virtual void ComponentAdded(SharedPointer<IComponent> component) { }

		virtual void ComponentRemoved(SharedPointer<IComponent> component) { }

		virtual void ComponentsRemoved(DynamicArray<SharedPointer<IComponent>>& components) { }

		// Getters
	public:
		inline DynamicArray<SharedPointer<IComponent>>& GetComponents() { return m_Components; }

		// Actions
	public:
		void AddComponent(SharedPointer<IComponent> component);

		void RemoveComponent(SizeT index);

		void RemoveComponents();
	};
}