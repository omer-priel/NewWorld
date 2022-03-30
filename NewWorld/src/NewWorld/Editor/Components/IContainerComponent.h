#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/IComponent.h"

namespace NewWorld::Editor::Components
{
	class IContainerComponent : virtual public IComponent
	{
	NW_CLASS(NewWorld::Editor::Components, IContainerComponent)

		// Override
	public:
		void Destroy() override
		{
			RemoveComponents();
		}

		// Getters
	public:
		virtual inline DynamicArray<SharedPointer<IComponent>>& GetSubComponents() = 0;

		// Events
	public:
		virtual void ComponentAdded(SharedPointer<IComponent> component) { }

		virtual void ComponentRemoved(SharedPointer<IComponent> component) { }

		virtual void ComponentsRemoved() { }

		// Actions
	public:
		void AddComponent(SharedPointer<IComponent> component)
		{
			GetSubComponents().push_back(component);
			component->SetWindow(GetWindow());

			component->Create();

			ComponentAdded(component);
		}

		void RemoveComponent(SizeT index)
		{
			auto& components = GetSubComponents();
			ComponentRemoved(components[index]);

			components[index]->Destroy();

			components.erase(components.begin() + index);
		}

		void RemoveComponents()
		{
			auto& components = GetSubComponents();
			if (!components.empty())
			{
				ComponentsRemoved();

				DynamicArray<SharedPointer<IComponent>>::iterator iter = components.begin();
				++iter;
				while (iter != components.end())
				{
					IComponent& component = *(*iter);

					component.Destroy();

					++iter;
				}

				components.clear();
			}
		}
	};
}