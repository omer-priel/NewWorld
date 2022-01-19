#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/ComponentContainer.h"

namespace NewWorld::Editor::UI
{
	class Panel : public ComponentContainer
	{
	NW_CLASS(NewWorld::Editor::UI, Panel)

		// Members
	public:
		

	public:
		Panel(uint x, uint y, uint width, uint height)
			: ComponentContainer(x, y, width, height)
		{

		}

		// Override
	public:
		virtual void Create() override { }
		virtual void Destroy() override { }

		virtual void ComponentAdded(Component& component) override { }

		virtual void ComponentsRemoved(DynamicArray<Component>& components) override { }
	};
}