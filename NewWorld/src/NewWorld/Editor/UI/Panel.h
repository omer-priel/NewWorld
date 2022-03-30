#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Components/ResizableComponent.h"
#include "NewWorld/Editor/Components/IContainerComponent.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"

namespace NewWorld::Editor::UI
{
	class Panel : public Components::ResizableComponent, virtual public Components::IContainerComponent
	{
	NW_CLASS(NewWorld::Editor::UI, Panel)

		// Members
	private:
		DynamicArray<SharedPointer<IComponent>> m_SubComponents;

		Graphics::Color m_BackgroundColor;

	public:
		Panel(float x, float y, float width, float height, const Graphics::Color& backgroundColor = Graphics::Colors::EditorBackground)
			: Components::ResizableComponent(x, y, width, height), m_BackgroundColor(backgroundColor)
		{

		}

		// Getters
	public:
		virtual inline DynamicArray<SharedPointer<IComponent>>& GetSubComponents() { return m_SubComponents; }

		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }

		inline Graphics::Color& GetBackgroundColor() { return m_BackgroundColor; }

		// Setters
	public:
		void SetBackgroundColor(const Graphics::Color& backgroundColor) { m_BackgroundColor = backgroundColor; }

		// Events
	public:
		void Update() override;

		void Destroy() override;

		void MouseKeyPressed(Input::Key key, float xPos, float yPos) override;

		void MouseKeyReleased(Input::Key key, float xPos, float yPos) override;

		void MouseHover(float xPos, float yPos) override;
	};
}