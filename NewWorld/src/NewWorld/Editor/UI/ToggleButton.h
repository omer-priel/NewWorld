#pragma once

#include "NewWorld/Minimal.h"
#include "NewWorld/Editor/Component.h"
#include "NewWorld/Graphics/Color.h"
#include "NewWorld/Graphics/Colors.h"

namespace NewWorld::Editor::UI
{
	class ToggleButton : public Component
	{
	NW_CLASS(NewWorld::Editor::UI, ToggleButton)

		// Members
	private:
		bool m_Checked;

		Graphics::Color m_BackgroundColor;
		Graphics::Color m_BackgroundCheckedColor;
		Graphics::Color m_ForegroundColor;

	public:
		ToggleButton(uint x, uint y, bool checked = false,
			const Graphics::Color& backgroundColor = Graphics::Colors::EditorDarkInputBackground,
			const Graphics::Color& backgroundCheckedColor = Graphics::Colors::EditorBlueInputBackground,
			const Graphics::Color& foregroundColor = Graphics::Colors::EditorLightValue)
			: Component(x, y, 30, 14), m_Checked(checked),
			m_BackgroundColor(backgroundColor), m_BackgroundCheckedColor(backgroundCheckedColor),
			m_ForegroundColor(foregroundColor)
		{

		}

		// Events
	public:
		void Update() override;

		void Click() override;

		// Getters
	public:
		inline bool IsChecked() const  { return m_Checked; }

		inline const Graphics::Color& GetBackgroundColor() const { return m_BackgroundColor; }
		inline const Graphics::Color& GetBackgroundCheckedColor() const { return m_BackgroundCheckedColor; }
		inline const Graphics::Color& GetForegroundColor() const { return m_ForegroundColor; }

		// Setters
	public:
		void SetX(uint x) { m_X = x; }
		void SetY(uint y) { m_Y = y; }

		void SetChecked(bool checked) { m_Checked = checked; }

		void SetBackgroundColor(const Graphics::Color& color) { m_BackgroundColor = color; }
		void SetBackgroundCheckedColor(const Graphics::Color& color) { m_BackgroundCheckedColor = color; }
		void SetForegroundColor(const Graphics::Color& color) { m_ForegroundColor = color; }

		// Actions
	public:
		void Toggle() { m_Checked = !m_Checked; }
	};
}