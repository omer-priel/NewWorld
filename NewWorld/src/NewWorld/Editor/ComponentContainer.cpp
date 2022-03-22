#include "nwpch.h"
#include "ComponentContainer.h"

#include "NewWorld/Editor/Graphics2D/LocalPainter.h"

namespace NewWorld::Editor
{
	// Override
	void ComponentContainer::Update()
	{
		Graphics2D::LocalPainter::Enter(*this);

		for (SharedPointer<Component>& component : m_Components)
		{
			component->Update();
		}

		Graphics2D::LocalPainter::Leave(*this);

		Component::Update();
	}
}