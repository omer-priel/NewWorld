#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/ComponentContainer.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"

namespace NewWorld::Editor::UI
{
	class Panel : public ComponentContainer
	{
	NW_CLASS(NewWorld::Editor::UI, Panel)

		// Members
	private:
		Graphics::Color m_BackgroundColor;

	public:
		Panel(uint x, uint y, uint width, uint height, const Graphics::Color& backgroundColor = Graphics::Colors::EditorBackground)
			: ComponentContainer(x, y, width, height), m_BackgroundColor(backgroundColor)
		{

		}

		// Override
	public:
		void Create() override;
		void Destroy() override;

		void OnUpdate() override;

		void ComponentAdded(Component& component) override;

		void ComponentsRemoved(DynamicArray<Component>& components) override;

		// Getters
	public:
		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }

		inline Graphics::Color& GetBackgroundColor() { return m_BackgroundColor; }

		// Setters
		void SetBackgroundColor(const Graphics::Color& backgroundColor)
		{
			m_BackgroundColor = backgroundColor;
		}
	};
}