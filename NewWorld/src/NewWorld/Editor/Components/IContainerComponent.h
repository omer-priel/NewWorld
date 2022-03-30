#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/IComponent.h"

namespace NewWorld::Editor::Components
{
	class IContainerComponent : virtual public IComponent
	{
	NW_CLASS(NewWorld::Editor::Components, IContainerComponent)

		// Actions
	public:
		virtual void ComponentAdded(SharedPointer<IComponent> component) { }

		virtual void ComponentRemoved(SharedPointer<IComponent> component) { }

		virtual void ComponentsRemoved(DynamicArray<SharedPointer<IComponent>>& components) { }

		// Getters
	public:
		virtual inline DynamicArray<SharedPointer<IComponent>>& GetComponents() = 0;

		// Actions
	public:
		void AddComponent(SharedPointer<IComponent> component)
		{
			GetComponents().push_back(component);
			component->SetWindow(GetWindow());

			component->Create();

			ComponentAdded(component);
		}

		void RemoveComponent(SizeT index)
		{
			auto& components = GetComponents();
			ComponentRemoved(components[index]);

			components[index]->Destroy();

			components.erase(components.begin() + index);
		}

		void RemoveComponents()
		{
			auto& components = GetComponents();
			if (!components.empty())
			{
				ComponentsRemoved(components);

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