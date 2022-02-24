#include "nwpch.h"
#include "ComponentContainer.h"

#include "NewWorld/Graphics/LocalPainter.h"

namespace NewWorld::Editor
{
	// Override
	void ComponentContainer::Update()
	{
		Graphics::LocalPainter::Enter(this);

		for (SharedPointer<Component>& component : m_Components)
		{
			component->Update();
		}

		Graphics::LocalPainter::Leave(this);

		Component::Update();
	}
}