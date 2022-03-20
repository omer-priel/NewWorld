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
		Panel(float x, float y, float width, float height, const Graphics::Color& backgroundColor = Graphics::Colors::EditorBackground)
			: ComponentContainer(x, y, width, height), m_BackgroundColor(backgroundColor)
		{

		}

		// Events
	public:
		void Update() override;

		void MouseKeyPressed(Input::Key key, float xPos, float yPos) override;

		void MouseKeyReleased(Input::Key key, float xPos, float yPos) override;

		void MouseHover(float xPos, float yPos) override;

		// Getters
	public:
		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }

		inline Graphics::Color& GetBackgroundColor() { return m_BackgroundColor; }

		// Setters
	public:
		void SetX(float x) { m_X = x; }
		void SetY(float y) { m_Y = y; }

		void SetWidth(float width) { m_Width = width; }
		void SetHeight(float height) { m_Height = height; }

		void SetBackgroundColor(const Graphics::Color& backgroundColor) { m_BackgroundColor = backgroundColor; }
	};
}