#include "nwpch.h"
#include "ComponentContainer.h"

#include "NewWorld/Editor/Graphics/LocalPainter.h"

namespace NewWorld::Editor
{
	// Override
	void ComponentContainer::Update()
	{
		Editor::Graphics::LocalPainter::Enter(*this);

		for (SharedPointer<Component>& component : m_Components)
		{
			component->Update();
		}

		Editor::Graphics::LocalPainter::Leave(*this);

		Component::Update();
	}
}